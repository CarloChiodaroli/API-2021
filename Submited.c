#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define NO_CONNESSIONE 0
#define TRUE 1
#define TRUEPRONTO 0
#define FALSE 0
#define SPAZIO ' '
#define RIF 1

typedef struct GDescritt {
	unsigned int indice;
	unsigned int Sum;
	struct GDescritt *prec;
	struct GDescritt *succ;
}GDescrittore;

typedef struct Nod {
	unsigned int peso;
	unsigned char pronto;
}TNodo;	

unsigned int k, d, due;

unsigned char tt0 = FALSE;

GDescrittore* Descrittore,* DescrCapo,* DescrAttuale,* DescrMassimo;

unsigned int scanld(){
	char tmpv;
	unsigned int tmp = 0;
	if(stdin->_IO_read_ptr >= stdin->_IO_read_end) tmpv = __uflow(stdin);
	else tmpv = (unsigned char) *(stdin->_IO_read_ptr++);
	if(tmpv =='\n') {
		if(stdin->_IO_read_ptr >= stdin->_IO_read_end) tmpv = __uflow(stdin);
		else tmpv = (unsigned char) *(stdin->_IO_read_ptr++);
	}
	while(tmpv != ',' && tmpv != '\n'){
		tmp = (tmp)*10 + (int)(tmpv - '0');
		if(stdin->_IO_read_ptr >= stdin->_IO_read_end) tmpv = __uflow(stdin);
		else tmpv = (unsigned char) *(stdin->_IO_read_ptr++);
	}
	return tmp;
}

int AggiungiGrafo(_Bool Ins, TNodo* NodoVett, off_t* CapoLettura) {
	unsigned int IRiga;
	unsigned int tmp, NodoIAttuale, NodoIMinimo;
	unsigned char zafatt = FALSE;
	unsigned char trash, flag = TRUE;

	if(stdin->_IO_read_ptr >= stdin->_IO_read_end) trash = __uflow(stdin);
	else trash = (unsigned char) *(stdin->_IO_read_ptr++);
	for (IRiga = 0; IRiga < d; IRiga++) {
		while (trash != ',') 
			if(stdin->_IO_read_ptr >= stdin->_IO_read_end) trash = __uflow(stdin);
			else trash = (unsigned char) *(stdin->_IO_read_ptr++);
		CapoLettura[IRiga] = ftello(stdin);
		stdin->_IO_read_ptr = stdin->_IO_read_ptr + due;
		while (trash != '\n') 
			if(stdin->_IO_read_ptr >= stdin->_IO_read_end) trash = __uflow(stdin);
			else trash = (unsigned char) *(stdin->_IO_read_ptr++);
	}
	
	IRiga = 0;
	
	CICLOB: 
	fseeko(stdin, CapoLettura[IRiga], SEEK_SET);
	NodoIMinimo = 0;
	NodoIAttuale = 1;
	while(NodoIAttuale!=d) {
		if (NodoVett[NodoIAttuale].pronto && NodoIAttuale != IRiga) {
			if ((tmp = scanld())) {
				tmp += NodoVett[IRiga].peso;
				if(NodoVett[NodoIAttuale].peso >= tmp) NodoVett[NodoIAttuale].peso = tmp;
			}
			if(NodoVett[NodoIAttuale].peso < NodoVett[NodoIMinimo].peso) NodoIMinimo = NodoIAttuale;
			if(!IRiga && NodoVett[RIF].peso != NodoVett[NodoIAttuale].peso) flag = FALSE;
		}
		else {
			do{
				if(stdin->_IO_read_ptr >= stdin->_IO_read_end) trash = __uflow(stdin);
				else trash = (unsigned char) *(stdin->_IO_read_ptr++);
			} while (trash != ',' && trash != '\n');
		}
		NodoIAttuale++;
	}

	if(!NodoIMinimo){ 
		IN_IF:
		if(!Ins) while(!(DescrAttuale->Sum)){ 
			if(DescrAttuale->succ == DescrAttuale) {
				tt0 = TRUE;
				return FALSE;
			} 
			else DescrAttuale = DescrAttuale->succ;
		}
		if(DescrAttuale == DescrCapo){
			DescrCapo = Descrittore;
			Descrittore->succ = DescrAttuale;
			DescrAttuale->prec = Descrittore;
			return TRUE;
		}
		else if(Descrittore == DescrMassimo){
			DescrAttuale->succ = Descrittore;
			Descrittore->prec = DescrAttuale;
			Descrittore->succ = Descrittore;
			return TRUE;
		}
		else {
			DescrAttuale->prec->succ = Descrittore;
			Descrittore->prec = DescrAttuale->prec;
			Descrittore->succ = DescrAttuale;
			DescrAttuale->prec = Descrittore;
			return TRUE;
		}
	}

	IRiga = NodoIMinimo;
	NodoVett[IRiga].pronto = TRUEPRONTO;
	Descrittore->Sum += NodoVett[IRiga].peso;
	while (Descrittore->Sum >= DescrAttuale->Sum && !zafatt){
		if(DescrAttuale->succ == DescrAttuale){
			if(Ins) {
				DescrMassimo = Descrittore;
				zafatt = TRUE;
				goto CICLOB;
			}
			else {
				return FALSE;	
			}
		}
		else DescrAttuale = DescrAttuale->succ;
	}
	if(flag) goto IN_IF;
	goto CICLOB;
	return FALSE;
}

void TopK(GDescrittore* Vettore) { 
	char tmpv, i;
	unsigned int oggetto, divisore;
	_Bool flag;
	if(Vettore->indice){
		while(Vettore != Vettore->succ){
			if(!Vettore->indice){
				if(stdout->_IO_write_ptr >= stdout->_IO_write_end) __overflow(stdout, '0');
				else (unsigned char) (*(stdout->_IO_write_ptr++) = '0');
			}
			else{
				flag = FALSE;
				divisore = 10000000;
				oggetto = Vettore->indice;
				for(i=7; i>=0; i--){
					tmpv = (unsigned char)(oggetto/divisore);
					oggetto = oggetto%divisore;
					if(tmpv && !flag) {
						flag = TRUE; 
						goto POI;
					}
					if(flag) {
						POI:
						if(stdout->_IO_write_ptr >= stdout->_IO_write_end) {tmpv = __overflow(stdout, tmpv+'0');}
						else {(unsigned char) (*(stdout->_IO_write_ptr++) = tmpv+'0');}
					}
					divisore = divisore/10;
				}
			}
			Vettore = Vettore->succ;
			if(stdout->_IO_write_ptr >= stdout->_IO_write_end) __overflow(stdout, SPAZIO);
			else (unsigned char) (*(stdout->_IO_write_ptr++) = SPAZIO);
		}
		if(!Vettore->indice){
			if(stdout->_IO_write_ptr >= stdout->_IO_write_end) __overflow(stdout, '0');
			else (unsigned char) (*(stdout->_IO_write_ptr++) = '0');
		}
		else {
			flag = FALSE;
			divisore = 10000000;
			oggetto = Vettore->indice;
			for(i=7; i>=0; i--){
				tmpv = (unsigned char)(oggetto/divisore);
				oggetto = oggetto%divisore;
				if(tmpv && !flag) flag = TRUE; 
				if(flag) {
					if(stdout->_IO_write_ptr >= stdout->_IO_write_end) {tmpv = __overflow(stdout, tmpv+'0');}
					else {(unsigned char) (*(stdout->_IO_write_ptr++) = tmpv+'0');}
				}
				divisore = divisore/10;
			}
		}
	}
	if(stdout->_IO_write_ptr >= stdout->_IO_write_end) __overflow(stdout, '\n');
	else (unsigned char) (*(stdout->_IO_write_ptr++) = '\n');
	return;
}

void MainSupporto(){
	int DimDescr, DimVettNod, IRiga;
	long unsigned int Indice;
	char com, trash = '\n';
	TNodo Nodi[d];
	off_t VettoreRighe[d];
	_Bool flag;
	trash = trash;

	DimDescr = sizeof(GDescrittore);
	DimVettNod = sizeof(TNodo) * (d-1);
	memset(Nodi, 255, sizeof(TNodo));
	memset(&Nodi[1], 255, DimVettNod);

	DescrMassimo = NULL;
	Indice = 0;
	Descrittore = malloc(DimDescr);
	Descrittore->indice = 0;
	Descrittore->succ = Descrittore;
	Descrittore->prec = Descrittore;
	DescrCapo = Descrittore;

	if(stdin->_IO_read_ptr >= stdin->_IO_read_end) com = __uflow(stdin);
	else com = (unsigned char) *(stdin->_IO_read_ptr++);

	CICLOA:	
	do{
		if(stdin->_IO_read_ptr >= stdin->_IO_read_end) trash = __uflow(stdin);
		else trash = (unsigned char) *(stdin->_IO_read_ptr++);
	}while(trash != '\n');
	if (com == 'A') {
		if(!tt0){	
			Descrittore->indice = Indice;
			Descrittore->Sum = 0;
			DescrAttuale = DescrCapo;
			if ((AggiungiGrafo( flag = (Indice<k), Nodi, VettoreRighe))){
				if(flag){
					Descrittore = malloc(DimDescr);
				}	
				else {
					Descrittore = DescrMassimo;
					DescrMassimo = DescrMassimo->prec;
					DescrMassimo->succ = DescrMassimo;
				}
			}
			
			memset(&Nodi[1], 255, DimVettNod);
			Indice++;
			if(stdin->_IO_read_ptr >= stdin->_IO_read_end) com = __uflow(stdin);
			else com = (unsigned char) *(stdin->_IO_read_ptr++);
			goto CICLOA;
		}
		else{
			if(stdin->_IO_read_ptr >= stdin->_IO_read_end) trash = __uflow(stdin);
			else trash = (unsigned char) *(stdin->_IO_read_ptr++);
			for (IRiga = 0; IRiga < d; IRiga++) {
				while (trash != '\n') 
					if(stdin->_IO_read_ptr >= stdin->_IO_read_end) trash = __uflow(stdin);
					else trash = (unsigned char) *(stdin->_IO_read_ptr++);
			}
			if(stdin->_IO_read_ptr >= stdin->_IO_read_end) com = __uflow(stdin);
			else com = (unsigned char) *(stdin->_IO_read_ptr++);
			goto CICLOA;
		}
	}
	else if (com == 'T') {
		TopK(DescrCapo);
		if(stdin->_IO_read_ptr >= stdin->_IO_read_end) com = __uflow(stdin);
		else com = (unsigned char) *(stdin->_IO_read_ptr++);
		if((stdin->_flags & _IO_EOF_SEEN)) return;
		else goto CICLOA;
	}
	else{
		if(stdin->_IO_read_ptr >= stdin->_IO_read_end) com = __uflow(stdin);
		else com = (unsigned char) *(stdin->_IO_read_ptr++);
	}
	goto CICLOA;
	return;
}

int main() {
	char trash;
	trash = '\0';
	d = scanf("%d", &d) * d;
	due = d*2 - 3;
	k = scanf("%d", &k) * k;
	if(stdin->_IO_read_ptr >= stdin->_IO_read_end) trash = __uflow(stdin);
	else trash = (unsigned char) *(stdin->_IO_read_ptr++);
	trash = trash;
	MainSupporto();
	return 0;
}