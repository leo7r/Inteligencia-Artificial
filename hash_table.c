/*
 * =====================================================================================
 *
 *       Filename:  hash_table.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/04/14 18:53:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

long long fact(int n){
    long long a = 1;
    int b = 1;
    while (b != n+1){
        a = a * b;
        b++;
    }
    return a;
}


