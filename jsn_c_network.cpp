#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



static void bitprint(const char *prefix, struct in_addr addr);

int main(int argc, char **argv)
{
struct in_addr ipaddr, netmask, network, broadcast;
if(argc != 3) {
fprintf(stderr, "use: %s ipaddr netmask\n"
"exemplo: %s 192.168.15.2 255.255.255.128\n",
*argv, *argv);
return 1;
}


/* converte o IP para network byte order, salva o resultado em ‘ipaddr’ */
if(!inet_aton(argv[1], &ipaddr)) {
fprintf(stderr, "endereço (ipaddr=%s) inválido!\n", argv[1]);
return 1;
}


if(!inet_aton(argv[2], &netmask)) {
fprintf(stderr, "endereço (netmask=%s) inválido\n", argv[2]);
return 1;
}



/* calcula o address */
network.s_addr = ipaddr.s_addr & netmask.s_addr;
/* calcula o broadcast */
broadcast.s_addr = netmask.s_addr ^ ~network.s_addr;
/* saida de todos os endereços */
bitprint("ipaddr: ", ipaddr);
bitprint("netmask: ", netmask);
bitprint("network: ", network);
bitprint("broadcast: ", broadcast);
return 0;
}
static void bitprint(const char *prefix, struct in_addr addr)
{


int i;
/* utiliza ‘mask’ para imprimir apenas os bits ligados
* e ‘dots’ para saber quando deve imprimir um ‘.’ */
unsigned long int mask = 0x80000000, dots = 0x01010100;
118
/* imprime o prefixo */
fprintf(stdout, "%s", prefix);
/* assume-se endereços 32 bits, sizeof(long int) */
for(i = 0; i < 32; i++) {
fprintf(stdout, "%d", addr.s_addr & mask ? 1 : 0);
if(mask & dots) fprintf(stdout, ".");
mask > >= 1;
}




/* imprime o endereço em notação decimal */
fprintf(stdout, " (%s)\n", inet_ntoa(addr));
}



