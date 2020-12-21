#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm which works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code. 

  Compile with:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    ./CrackAZ99-With-Data > results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2019
******************************************************************************/
int n_pass = 4;

char *encrypted_passwords[] = {
 "$6$KB$6SsUGf4Cq7/Oooym9WWQN3VKeo2lynKV9gXVyEG4HvYy1UFRx.XAye89TLp/OTcW7cGpf9UlU0F.cK/S9CfZn1",
  "$6$KB$.bVspZYQofaBc4KhsjlqZSxu4R7r7mH7.Q/uCYlJ.3nRV2x5Jz.TKYX6Aa97sUZhTjmN3rett7GrCFr3aO3uR/",
  "$6$KB$wO5OXgJxqVzltwW29G/XJuG5ZszGOhwhvpEBnFM/ThGmTNiNhnUTBS8lnNWs6SwP6XpUwzKXVTv90S2XEWwy./",
  "$6$KB$JXfY4sYXD0vnuRY3KIvezu913aIc1TJ0CE0oVTWDrsRSXk4/k.RnljKOR3/Vw7wxAOnEsxllD01WU/MJP4IIj1"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 In this function, it can crack the kind of password given above. In result, 
 when the password is found, # is kept at the start of the line. In this type of program 
 comment out he printfs should not included because it is one of the most time consuming
 operations.
*/

void crack(char *salt_and_encrypted){
  int p, q, r;     // Counters loop
  char salt[7];    // Need space for \0 while string used in hashing the password.
  char plain[7];   // Checks the combination of letter
  char *encrypt;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(p='A'; p<='Z'; p++){
    for(q='A'; q<='Z'; q++){
      for(r=0; r<=99; r++){
        sprintf(plain, "%c%c%02d", p, q, r); 
        encrypt = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, encrypt) == 0){
          printf("#%-8d%s %s\n", count, plain, encrypt);
        } else {
          printf(" %-8d%s %s\n", count, plain, encrypt);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}
/*Calculate the difference between two times and returns zero on
  success and the time difference through an argument. It will 
  be unsuccessful if the start time is after the end time. */

int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main(int argc, char *argv[])
 {
  int i;
 struct timespec start, finish;   
  long long int time_elapsed;
 
  clock_gettime(CLOCK_MONOTONIC, &start);

  for(i=0;i<n_pass;i<i++) 
 {
    crack(encrypted_passwords[i]);
 }
  clock_gettime(CLOCK_MONOTONIC, &finish);
   time_difference(&start, &finish, &time_elapsed);
   printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9)); 

  return 0;
  }




 
  

  


