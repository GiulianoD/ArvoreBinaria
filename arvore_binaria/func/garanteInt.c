int garanteInt(){
    int valor, aux = -1;
    char letra;

    do{
        aux = scanf("%d", &valor);
        do{
            letra = getchar();
        }while(letra != '\n');
    }while(aux == 0);

    return valor;
}