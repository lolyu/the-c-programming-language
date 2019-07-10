#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NULL            0
#define EOF             -1
#define BUFSIZ          1024
#define OPEN_MAX        20
#define PERMS           0666
#define max(x, y)       ((x) > (y)) ? (x) : (y)

struct _flags {
    unsigned int _READ: 1;      // file open for reading
    unsigned int _WRITE: 1;     // file open for writing
    unsigned int _UNBUF: 1;     // file is unbuffered
    unsigned int _EOF: 1;       // EOF
    unsigned int _ERR: 1;       // error
};


typedef struct _iobuf {
    int cnt;                // characters left
    char *ptr;              // next character position
    char *base;             // location of buffer
    struct _flags flag;     // mode of file access
    int fd;                 // file descriptor
} _FILE;

extern _FILE _iob[OPEN_MAX] = {
        {0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0}, 0},
        {0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0}, 1},
        {0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 2}
};

#define _stdin              (&_iob[0])
#define _stdout             (&_iob[1])
#define _stderr             (&_iob[2])
#define _SEEK_SET           0
#define _SEEK_CUR           1
#define _SEEK_END           2

int _getc(_FILE *);
int _putc(int, _FILE *);

int _fillbuf(_FILE *);
int _flushbuf(int, _FILE *);
_FILE *_fopen(const char *, const char *);
int _fflush(_FILE *);
int _fclose(_FILE *);
int _fseek(_FILE *, long, int);
void _clearflag(struct _flags *);

#define _feof(p)         ((p)->flag._EOF != 0)
#define _ferror(p)       ((p)->flag._ERR != 0)
#define _fileno(p)       ((p)->fd)

void _clearflag(struct _flags *f) {
    f->_READ = f->_WRITE = f->_ERR = f->_UNBUF = f->_EOF = 0;
}


int _getc(_FILE *fp) {
    return (--(fp)->cnt >= 0 ? (unsigned char) *(fp)->ptr++ : _fillbuf(fp));
}

int _putc(int c, _FILE *fp) {
    return (--(fp)->cnt >= 0 ? *(fp)->ptr++ = (c) : _flushbuf((c), fp));
}


#define _getchar()       _getc(_stdin)
#define _putchar(x)      _putc(x, _stdout)


int _fillbuf(_FILE *fp) {
    int bufsize;
    if (!fp->flag._READ || fp->flag._EOF || fp->flag._ERR)
        return EOF;
    bufsize = fp->flag._UNBUF ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize * sizeof(char))) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (fp->cnt <= 0) {
        if (fp->cnt == 0)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    --fp->cnt;
    return (unsigned char) *fp->ptr++;
}


int _flushbuf(int c, _FILE *fp) {
    int n, bufsize;
    if (!fp->flag._WRITE || fp->flag._EOF || fp->flag._ERR)
        return EOF;
    if (fp->base == NULL && !fp->flag._UNBUF)
        if ((fp->base = (char *)malloc(BUFSIZ * sizeof(char))) == NULL)
            fp->flag._UNBUF = 1;
        else {
            fp->ptr = fp->base;
            fp->cnt = BUFSIZ - 1;
        }
    if (fp->flag._UNBUF) {
        fp->ptr = fp->base = NULL;
        fp->cnt = 0;
        if (c == EOF)
            return c;
        n = write(fp->fd, &c, 1);
        bufsize = 1;
    } else {
        if (c != EOF)
            *fp->ptr++ = c;
        bufsize = (int)(fp->ptr - fp->base);
        n = write(fp->fd, fp->base, bufsize);
        fp->ptr = fp->base;
        fp->cnt = BUFSIZ - 1;
    }
    if (n == bufsize)
        return c;
    else {
        fp->flag._ERR = 1;
        return EOF;
    }
}


int _fflush(_FILE *fp) {
    int ret;
    int i;

    ret = 0;
    if (fp == NULL) {
        for (i = 0; i < OPEN_MAX; ++i)
            if (_iob[i].flag._WRITE == 1 && fflush(&_iob[i]) == EOF)
                ret = EOF;
    } else {
        if (fp->flag._WRITE == 0)
            return EOF;
        _flushbuf(EOF, fp);
        if (fp->flag._ERR)
            ret = EOF;
    }
    return ret;
}


_FILE *_fopen(const char *name, const char *mode) {
    int fd;
    _FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; ++fp)
        if (fp->flag._READ == 0 && fp->flag._WRITE == 0)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;
    switch (*mode) {
        case 'w':
            fd = creat(name, PERMS);
            break;
        case 'a':
            if ((fd = open(name, O_WRONLY, 0)) == -1)
                fd = creat(name, PERMS);
            lseek(fd, 0, SEEK_END);
            break;
        case 'r':
            fd = open(name, O_RDONLY, 0);
            break;
        default:
            return NULL;
    }
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->flag._READ = 1;
    else
        fp->flag._WRITE = 1;
    return fp;
}

int _fclose(_FILE *fp) {
    int fd;
    if (fp == NULL)
        return EOF;
    _fflush(fp);
    if (fp->flag._ERR)
        return EOF;
    fp->cnt = 0;
    if(fp->base)
        free(fp->base);
    fp->ptr = fp->base = NULL;
    _clearflag(&fp->flag);
    fd = fp->fd;
    fp->fd = -1;
    return close(fd);
}

int _fseek(_FILE *fp, long offset, int whence) {
    int ret;
    if (fp->flag._UNBUF == 0 && fp->base != NULL) {
        if (fp->flag._WRITE) {
            if (_fflush(fp))
                return EOF;
        } else if (fp->flag._READ) {
            ret = lseek(fp->fd, 0, SEEK_CUR);
            if (whence == SEEK_CUR) {
                if (offset >= 0 && offset <= fp->cnt) {
                    fp->cnt -= offset;
                    fp->ptr += offset;
                    fp->flag._EOF = 0;
                    return ret - fp->cnt;
                } else
                    offset -= fp->cnt;
            }
            fp->cnt = 0;
            fp->ptr = fp->base;
        }
    }
    ret = lseek(fp->fd, offset, whence);
    if (ret >= 0)
        fp->flag._EOF = 0;
    return ret;
}


int main(int argc, char *argv[]) {
    // const char s[] = "helloworld\n";
    // for (int i = 0; i < 11; ++i)
    //    _putchar(s[i]);
    // _fflush(_stdout);
    _FILE *fp;
    int c, pos;
    fp = _fopen("main.c", "r");
    if (fp == NULL) {
        fprintf(stderr, "error opening file.");
        exit(EXIT_FAILURE);
    }
    while ((c = _getc(fp)) != EOF)
        _putc(c, _stdout);
    _fflush(_stdout);
    pos = _fseek(fp, 0, _SEEK_CUR);
    printf("\nPOSITION: %d\n", pos);
    return 0;
}
