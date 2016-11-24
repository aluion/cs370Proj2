#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <string.h>
#define MAX_HASH_LEN 6

int createHexValue(){
	sleep(1);
	return rand()%128;
	
}

char* createString(){
	printf("creating strings");
	char* string1;
	int i;

	for (i = 0 ; i < 6 ; i++){
		string1[i] = createHexValue();
		printf("string1 at i: %d,\n", string1[i]);
	}
	
	return string1;
	
} 

void weakCollision(const EVP_MD *md){
	printf("checking of weak collisons\n");
	unsigned char string1[3];
	unsigned char string2[3];
	int hash1, hash2, count, found;
	char begin, end;	
	printf("assigning md_values\n");
 	unsigned char md_value1[6];
 	unsigned char md_value2[6];
 	int md_len, i, j;
	end = (char)127;
	begin = (char)0;	
	
	i =0;
	j=0;
	EVP_MD_CTX *mdctx;
	md_len = 3;
	
		
	for (i = 0 ; i < 6 ; i++){
		string1[i] =  (char)abs(rand()%127) ;
		printf("%c\n", string1[i]);
	}

	for (i = 0 ; i < 6 ; i++){
		string2[i] =  (char)abs(rand()%127);
		printf("%c\n", string2[i]);
	}
	count = 0;
	found = 0;

	for( i = 0; i < strlen(string2); i++){
		for(j = 0; j < 128; j++){
			
 	/*mdctx = EVP_MD_CTX_create();
 	EVP_DigestInit_ex(mdctx, md, NULL);
 	EVP_DigestUpdate(mdctx, string1, strlen(string1));
 	EVP_DigestFinal_ex(mdctx, md_value1, &md_len);

 	EVP_DigestInit_ex(mdctx, md, NULL);
 	EVP_DigestUpdate(mdctx, string2, strlen(string2));
 	EVP_DigestFinal_ex(mdctx, md_value2, &md_len);
	EVP_MD_CTX_destroy(mdctx);
	EVP_cleanup();
	//printf("string1: %s, string2: %s \n", string1, string2);
	//printf("hash1: %x, hash2: %x\n", md_value1, md_value2 );
	*/
	
	//printf("hash functions, %x, %x\n", md_value1, md_value2);


		if ((strncmp(md_value1, md_value2,6)==0) & (strcmp(string1,string2)==0)){
			printf("weak collision found! %s ,%s" , string1, string2);
			found++;
		}
	
		printf("string2[i]: %c\n", string2[i]);
		if ((string2[i] ==  end)){
		printf("Greater than 128,\n");
		string2[i] = begin;
		}else{
		string2[i]++;
		printf("string2[i]++: %c\n", string2[i]);
		}
	}
	}	
	printf("Found %d collisons\n", found);
}

/*
void strongCollison(){

	if(hash == hash2){
		printf("strong collision found! %s ,%s" , string1, string2);
	
}
}*/




 main(int argc, char *argv[])
 {
 EVP_MD_CTX *mdctx;
 const EVP_MD *md;
 char mess1[] = "Test Message\n";
 char mess2[] = "Hello World\n";
 unsigned char md_value[MAX_HASH_LEN];
 int md_len, i;

srand(time(NULL));

//printf("evp_max_size:%d\n", EVP_MAX_MD_SIZE);
//printf("evp_max_size:%d\n", EVP_MAX_MD_SIZE);


 OpenSSL_add_all_digests();

 if(!argv[1]) {
 	printf("Usage: mdtest digestname\n");
	exit(1);
 }

 md = EVP_get_digestbyname(argv[1]);

 if(!md) {
 	printf("Unknown message digest %s\n", argv[1]);
	exit(1);
 }
/*
 mdctx = EVP_MD_CTX_create();
 EVP_DigestInit_ex(mdctx, md, NULL);
 EVP_DigestUpdate(mdctx, mess1, strlen(mess1));
 EVP_DigestUpdate(mdctx, mess2, strlen(mess2));
 EVP_DigestFinal_ex(mdctx, md_value, &md_len);
 EVP_MD_CTX_destroy(mdctx);

printf("md_value: %s\n", md_value);
printf("md_len: %d\n", md_len);


 printf("Digest is: ");
 for(i = 0; i < MAX_HASH_LEN; i++)
 	printf("%02x", md_value[i]);
 printf("\n");

(char)mess1[1]++;
printf("new string after increment: %s\n", mess1);
*/

weakCollision(md);


 /* Call this once before exit. */
 EVP_cleanup();
 exit(0);
}
