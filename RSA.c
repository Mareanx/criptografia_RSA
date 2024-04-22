#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int mdc(int a, int b)
{
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

void generateKey(int p, int q, int *publicKey, int *privateKey)
{
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 2;

    while (e < phi)
    {
        if (mdc(e, phi) == 1)
            break;
        else
            e++;
    }

    int d = 1;
    while (((d * e) % phi) != 1)
    {
        d++;
    }

    publicKey[0] = e;
    publicKey[1] = n;
    privateKey[0] = d;
    privateKey[1] = n;
}

int cripto(int msg, int *publicKey)
{
    int e = publicKey[0];
    int n = publicKey[1];
    long long result = 1;
    for (int i = 0; i < e; i++)
    {
        result = (result * msg) % n;
    }
    return (int)result;
}

int descripto(int msgCripto, int *privateKey)
{
    int d = privateKey[0];
    int n = privateKey[1];
    long long result = 1;
    while (d > 0)
    {
        if (d % 2 == 1)
        {
            result = (result * msgCripto) % n;
        }
        msgCripto = (msgCripto * msgCripto) % n;
        d /= 2;
    }
    return (int)result;
}

int main()
{
    int p = 61;
    int q = 53;
    int publicKey[2], privateKey[2];
    generateKey(p, q, publicKey, privateKey);

    int msg;
    printf("Digite no máximo 4 numeros: \n");
    scanf("%d", &msg);
    printf("Mensagem Original: %d\n", msg);

    int msg_criptografada = cripto(msg, publicKey);
    printf("Mensagem criptografada: %d\n", msg_criptografada);

    int msg_descriptografada = descripto(msg_criptografada, privateKey);
    printf("Mensagem descriptografada: %d\n", msg_descriptografada);

    return 0;
}
