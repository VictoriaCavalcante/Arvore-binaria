#include "arvorebinaria.h"

int main()
{
    printf("                     TRABALHO PRATICO 3 - ESTRUTURA DE DADOS\n\n\n");
    printf("Discentes: Andre Cacau e Victoria Cavalcante\n\n\n");
    printf("                                           Elaboracao do programa proposto pelo\n");
    printf("                                           professor  Raoni  para  obtencao  de\n");
    printf("                                           parte  da  nota  referente  a  N2 da\n");
    printf("                                           disciplina de Estrutura de  Dados do\n");
    printf("                                           curso de Bacharelado em  Sistemas de\n");
    printf("                                           Informacao da UFAC. Data: 01/12/2019\n");
    printf("\n________________________________________________________________________________");

    printf("\n\n                      OPERACOES COM ARVORE BINARIA DE BUSCA\n");

    Arvore *raiz = cria_arvore();
    int aux;
    while(1)
    {
        //Instrucoes
        printf("\n\n--------------------------------------------------------------------------------");
        printf("\n1  - Adicionar chaves");
        printf("\n2  - Imprimir com encaminhamento central");    //Funcao extra
        printf("\n3  - Imprimir com encaminhamento pos-fixado"); //Funcao extra
        printf("\n4  - Imprimir com encaminhamento pre-fixado"); //Funcao extra
        printf("\n5  - Remover todas as chaves");                //Funcao extra
        printf("\n6  - Verificar Arvore Vazia");                 //Funcao extra
        printf("\n7  - Buscar chave");
        printf("\n8  - Remover chave");
        printf("\n9  - Atualizar chave");
        printf("\n10 - Tamanho da arvore");
        printf("\n11 - Altura da arvore");
        printf("\n0  - Sair (remove a arvore alocada e finaliza o programa)"); //Antes de sair se ouver algum elemento na arvore ele eh liberado juntamente com ela

        printf("\nEscolha uma opcao: ");
        scanf("%d", &aux);

        if(aux == 1)
        {
            int num;
            printf("\nADICIONANDO CHAVES (Entre com 0 para finalizar as insercoes)");
            printf("\nInsira uma chave: ");
            scanf("%d", &num);
            while(num != 0)
            {
                insere(raiz, num);
                printf("\nInsira uma chave: ");
                scanf("%d", &num);
            }
            printf(">Entradas encerradas<");
        }
        else if(aux == 2)
        {
            printf("\nIMPRIMINDO CHAVES: *Central*\n");
            //funcao "vazia" utilizada para verificar se a arvore esta vazia, soh permite a chamada da funcao que imprime se ela retornar falso (nao vazia = 0)
            if(vazia(raiz))
                printf(">Arvore vazia<\n");
            else{
                printf("->|");central(raiz);printf("<-");}
        }
        else if(aux == 3)
        {
            printf("\nIMPRIMINDO CHAVES: *Pos-ordem*\n");
            if(vazia(raiz))
                printf(">Arvore vazia<\n");
            else{
                printf("->|");pos_ordem(raiz);printf("<-");}
        }
        else if(aux == 4)
        {
            printf("\nIMPRIMINDO CHAVES: *Pre-ordem*\n");
            if(vazia(raiz))
                printf(">Arvore vazia<\n");
            else{
                printf("->|");pre_ordem(raiz);printf("<-");}
        }
        else if(aux == 5)
        {
            printf("\nREMOVENDO TODA A ARVORE");
            libera_arvore(raiz);
            raiz = cria_arvore(); //Como explicado na funcao "libera_arvore" quando chamada ela libera totalmente a arvore, portando eh necessario inicializada novamente
        }
        else if(aux == 6)
        {
            printf("\nVERIFICANDO SE A ARVORE ESTA VAZIA\n");
            if(vazia(raiz))
                printf(">Arvore vazia<\n");
            else
                printf(">A Arvore nao esta vazia<\n");
        }
        else if(aux == 7)
        {
            int v;
            printf("\nBUSCANDO CHAVE");
            printf("\nQual o valor? ");
            scanf("%d", &v);
            busca(raiz, v);
        }
        else if(aux == 8)
        {
            int c;
            printf("\nREMOVENDO CHAVE");
            printf("\nInsira a chave a ser removida: ");
            scanf("%d", &c);
            remove_no(raiz, c);
        }
        else if(aux == 9)
        {
            //Nao foi preciso ser feita uma funcao para esta opcao:
            //Em vez disso bastou utilizar a funcao busca, remove e insere.
            //Foi feito desta maneira pois em uma arvore binaria de busca apenas atualizar um valor sem coloca-lo no lugar correto
            //pode comprometer a arvore, portanto para evitar isso o No escolhido eh devidamente removido e outro eh devidamente inserido
            int x, y;
            printf("\nATUALIZANDO CHAVE");
            printf("\nValor da chave: ");
            scanf("%d", &x);

            if(busca(raiz, x)) //Se a chave for encontrada{
            {
                printf("\nNovo valor: ");
                scanf("%d", &y);
                int i = insere(raiz, y);//insiro um novo No
                if(i){printf("\nSTATUS CHAVE ANTERIOR:");remove_no(raiz, x);}//e removo o antigo, somente se o novo a ser adicionado for valido.
            }                                                               //Por isso esta dentro deste if}
            else
                printf(">Nao foi possivel atualizar<\n"); //Se nao for encontrado nao ha como fazer a atualizacao
        }
        else if(aux == 10)
        {
            printf("\nTAMANHO DA ARVORE:\n");
            printf("> %d <\n", tamanho(raiz));
        }
        else if(aux == 11)
        {
            printf("\nALTURA DA ARVORE:\n");
            printf("> %d <\n", altura(raiz));
        }
        else if(aux == 0)
        {
            printf("\nSAINDO");
            libera_arvore(raiz); //Liberando toda a arvore caso exista antes de finalizar o programa
            break;
        }
        else
            printf("\n>Opcao invalida<\n");
    }

    printf("\nOBRIGADO POR UTILIZAR O PROGRAMA!!!\n"); //Feedback final apos saida

    return 0;
}
