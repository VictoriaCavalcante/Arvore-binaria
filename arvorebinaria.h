#include<stdio.h>
#include<stdlib.h>

//ESTRUTURAS UTILIZADAS
typedef struct No *Arvore; //Ponteiro para o inicio da arvore

struct No
{
    int info; //Chave
    struct No *esq; //Ponteiro para o No da esquerda
    struct No *dir; //Ponteiro para o No da direta
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FUNCAO PARA CRIAR A RAIZ DA ARVORE
Arvore* cria_arvore()
{
    Arvore *raiz = (Arvore*) malloc (sizeof(Arvore));//criando o No especial que aponta para o inicio da arvore
    *raiz = NULL;
    return raiz;
}

//FUNCAO PARA INSERIR OS NOS NA ARVORE
int insere(Arvore *raiz, int valor)
{
    struct No *novo = (struct No*) malloc(sizeof(struct No)); //Criando novo No
    novo->info = valor; //Atribuindo o valor para a sua chave
    novo->esq = NULL; //Sempre que um novo No for adicionado ele sera uma folha
    novo->dir = NULL; //Por isso que o campo esqeurda e direita dele sao NULL

    if(*raiz == NULL) //Se o conteudo da raiz for NULL quer dizer que nao ha elementos na arvore
        *raiz = novo; //Portanto basta apenas adiciona-lo
    else
    {
        //Se o No a ser inserido nao for o primeiro temos que encontrar o lugar onde ele vai ser inserido
        struct No *aux = *raiz; //Variavel para percorrer a Arvore
        struct No *ant = NULL; //Variavel para guardar o pai do novo No a ser inserido

        while(aux != NULL) //Enquanto a variavel auxiliar nao for uma folha ela sera incrementada, pois como dito anteriormente todos os Nos que forem adicionados serao uma folha
        {
            ant = aux; //Aqui a variavel eh guardada para sabermos onde o novo No sera adicionado (quem sera o seu pai)

            if(valor == aux->info) //Se o valor for igual nao pode ser adicionado para evitar complicacoes
            {
                free(novo); //Entao o novo No criado eh logo removido para nao ocupar espaco
                printf(">FALHOU< *Chave ja existente*\n");
                return 0; //Finaliza a funcao apos emitir a mensagem acima
            }

            if(valor < aux->info) //Isso nos dira para qual direcao seguir
                aux = aux->esq; //Se o valor for menor do que o valor do No que estamos no momento ele ira para esquerda
            else
                aux = aux->dir; //Se for maior ele ira para direita

            //Ao chegar no final ele saira do while entao teremos o pai do elemento a ser adicionado
        }

        //Agora basta ver se o novo No vai ser inserido na esquerda ou na direita de seu pai
        if(valor < ant->info)
            ant->esq = novo;
        else
            ant->dir = novo;
    }
    printf("CHAVE ADICIONADA\n"); //Feedback
    return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCAO PARA IMPRIMIR OS VALORES DOS NOS PELO ENCAMINHAMENTO CENTRAL (ordenado de forma crescente)
//O encaminhamento central consistem em visitar primeiro o No da esquerda depois a Raiz depois o No da direita
void central(Arvore *raiz)
{
    //A ideia eh estabelecer que em algum momento todos os Nos serao uma raiz, para ser mais preciso, no momento da impressao eh como se o No fosse uma raiz
    //A funcao eh chamada recursivamente e ao chegar no No folha havera o primeiro retorno pois seu campo esquerdo sera NULL
    //Ao seguir adiante "apos a chamada &(*raiz)->esq" o No eh imprimido e eh chamada "&(*raiz)->dir"
    if(*raiz == NULL)//Que se estiver NULL ele finalizara a chamada dando vez para as anteriores chamadas
        return;
    else        //mas se ele nao for NULL a chamada "&(*raiz)->dir" resultara em outra chamada recursiva
    {
        central(&(*raiz)->esq); //esta aqui, e apos terminar passara para a proxima linha imprimindo.
        printf(" %d |", (*raiz)->info);
        central(&(*raiz)->dir); //Por isso disse no comeco que eh estabelecido basicamente que todos serao raizes no momento de impressao, ate mesmo a folha
        //pois que para as outras chamadas serem efetuadas esta teria que ser completada indo ate o final para que acontecesse a parada ao ir a uma No que nao existe
    }
}

//O mesmo principio vale para os dois tipos de encaminhamento abaixo. Perceba que muda apenas a posicao do printf.
//FUNCAO PARA IMPRIMIR OS VALORES DOS NOS PELO ENCAMINHAMENTO POS FIXADO
void pos_ordem(Arvore *raiz)
{
    if(*raiz == NULL)
        return;
    else
    {
        pos_ordem(&(*raiz)->esq);
        pos_ordem(&(*raiz)->dir);
        printf(" %d |", (*raiz)->info);
    }
}

//FUNCAO PARA IMPRIMIR OS VALORES DOS NOS PELO ENCAMINHAMENTO PRE FIXADO
void pre_ordem(Arvore *raiz)
{
    if(*raiz == NULL)
        return;
    else
    {
        printf(" %d |", (*raiz)->info);
        pre_ordem(&(*raiz)->esq);
        pre_ordem(&(*raiz)->dir);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//FUNCAO PARA INFORMAR SE A ARVORE ESTA VAZIA
int vazia(Arvore *raiz)
{
    if(*raiz == NULL) //Se o conteudo da raiz for NULL retorna verdadeiro
        return 1;
    else
        return 0;    //Se nao, retorna falso
}

/////////////////////////////////////////////////////////////// FUNCOES PARA DESTRUIR...
void libera_no(struct No *nodo)
{
    //A funcao libera_no eh chamada recursivamente e comeca a remover a arvore pelas folhas para que nao percamos o acesso a nenhum No da arvore
    if(nodo == NULL)
        return;
    //Quando ele chegar no No folha havera a chamada "nodo->esq" que retornara NULL pois ele eh um No folha (nao possui filhos nem na esquerda nem na direita)
    //na chamada "nodo->dir" entao tambem retorna NULL, e finalmente o No eh liberado.
    //A chamada que chamou o No que foi liberado eh finalizada, ou seja o No da esquerda foi removido
    //Entao agr eh feito o mesmo procedimento no No da direita que apos finalizado retornara para a chamada anterior e assim sussessivamnte ate que todos sejam removidos
    libera_no(nodo->esq);
    libera_no(nodo->dir);
    free(nodo);
    nodo = NULL;
}

void libera_arvore(Arvore *raiz)
{
    //Esta funcao chama a funcao acima para liberar os Nos e apos todos os Nos serem liberados ela libera a raiz
    if(*raiz == NULL)//Se o conteudo da arvore for igual a NULL quer dizer que ela ja esta vazia
    {
        printf("\n>A Arvore ja esta vazia<\n");//Feedback
        return;
    }
    libera_no(*raiz);
    free(raiz); //Como no final eh removida a raiz eh importante lembrar de chamar a funcao cria novamente caso ainda seja desejado adicionar Nos
    //Caso nao seja mais utilizada, basta finalizar o programa. Esta funcao eh utilizada no comando sair quando eh solicitado a finalizacao do programa, para limpar o espaço utilizado pela arvore
    printf("\n>Arvore liberada<\n");
}
/////////////////////////////////////////////////////////////// ...TOTALMENTE A ARVORE (Libera todos os Nos e a raiz)

//FUNCAO PARA BUSCAR UMA CHAVE NA ARVORE
int busca(Arvore *raiz, int valor)
{
    if(*raiz == NULL)//Se o conteudo da raiz for igual a NULL ele emite a msg e finaliza a funcao
    {
        printf(">Arvore vazia<\n"); //Feedback
        return 0;//Encerra a funcao
    }

    struct No *aux = *raiz; //Variavel para percorrer a arvore
    while(aux != NULL)
    {
        if(valor == aux->info) //Se o valor for igual ao valor que guarda este No ele foi encontrado
        {
            printf(">Chave encontrada<\n");//Feedback
            return 1;//Encerra a funcao
        }
        if(valor < aux->info) //Sabemos como que as chaves sao inseridas na arvore binaria, entao procuramos o valor da mesma forma
            aux = aux->esq; //indo para a esquerda se for menor
        else
            aux = aux->dir; //ou indo para direita se for maior
    }
    //Esta msg eh emitida se o valor nao for encontrado
    printf(">Chave nao encontrada<\n"); //Feedback
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////FUNCOES PARA...
//A segunda funcao chamara a primeira para verificar os 3 casos de remocao: quando o No soh possui 1 filho, nenhum filho ou dois filhos
struct No *remove_nodo(struct No *nodo)
{
    //Primeiro verifica-se se o No possui dois filhos. Para isso eh verificado se seus campos esquerda e direita sao diferentes de NULL
    if(nodo->esq != NULL && nodo->dir != NULL)
    {
        //A regra eh que o No a direita do No a ser removido assume seu lugar e o No a esquerda dele ficara agora o mais a esquerda possivel do No da direita
        //Sendo assim precisamos guardar o No da direita, o da esquerda e depois colocar o No da esquerda o mais a esquerda possivel do No da direita

        struct No *aux1 = nodo->dir;//Guardando o No da direita
        struct No *aux2 = nodo->esq;//Guardando o No da esquerda
        struct No *aux3 = nodo->dir;//Variavel auxiliar para percorrer a Sub-arvore da direita para adicionar atraves da variavel
        struct No *ant = NULL;      //ant "anterior" (utilizada para guardar o No) o No da esquerda o mais a esquerda possivel dele
        free(nodo);//Ja podemos liberar o No pois salvamos tudo que precisamos

        while(aux3 != NULL) //Agora vamos percorrer a sub-arvore direita para saber onde adicionar o No da esquerda
        {
            ant = aux3; //Importante para nao perder o No que apontara para o No da esquerda que ira para esse local da arvore agora
            aux3 = aux3->esq; //Vai descendo ate o final do lado esquerdo, nao eh necessario mais nada pois queremos ir para esquerda somente
            //todos os nos da esquerda da subarvore direita serao maiores que o No esquerdo do nodo a ser removido
        }
        ant->esq = aux2; //quando chegar no final do lado mais a esquerda da sub-arvore direita conseguimos a posicao na qual o No da esquerda ficara agora

        return aux1; //Retornamos o No que substituira agora o No que foi removido
    }
    else if(nodo->esq == NULL) //Se o campo esquerdo for NULL ele pode ter um filho na direita ou nao.
    {
        struct No *aux1;
        aux1 = nodo->dir; //Portanto para nao perder o resto da arvore guardamos seu lado direito, se ele nao tiver nada no lado direito nao tem problema
        free(nodo);//Liberando o No
        return aux1; //pois o retorno sera NULL tmb, entao serve para estes dois casos (ter um filho na direita apenas ou nao ter nenhum filho)
    }
    else //Se o lado esquerdo nao estiver vazio
    {
        struct No *aux1;
        aux1 = nodo->esq; //Guardamos ele para nao perder um possivel resto da arvore
        free(nodo);//Liberamos o No
        return aux1;//Retornaos o No guardado
    }
}

//Esta funcao busca o No que sera removido e guarda seu antecessor(pai) para nao perdemos o restante da arvore caso a remocao seja no meio dela
int remove_no(Arvore *raiz, int valor)
{
    if(*raiz == NULL) //Se o conteudo da raiz for NULL a arvore esta vazia
    {
        printf(">Arvore vazia<\n"); //Feedback
        return 0;
    }

    struct No *ant = NULL; //Variavel para guardar o Pai do cara a ser removido
    struct No *nodo = *raiz; //Variavel para percorrer a arvore

    //Esta parte eh bem semelhante a funcao "busca", porem com uma peculiaridade
    while(nodo != NULL)
    {
        if(valor == nodo->info)//Se o valor for encontrado no decorrer da busca acontece o seguinte:
        {
            if(nodo == *raiz) //Se o valor for o primeiro elemento, ou seja, a raiz, nao sera preciso guardar seu anterior, pois ele nao tem pai entao nao havera necessidade de verificar para que lado o pai dele apontaria apos ele ser removido
                *raiz = remove_nodo(nodo);//Basta entao chamar a funcao remove_nodo que retornara o elemento que substituira a raiz removida, com base em alguma das 3 regras
            else
            {
                //Se nao, quer dizer que o No a ser removido nao eh a raiz, entao precisamos saber para onde o seu pai ira apontar agora, para esquerda ou para direita

                if(valor < ant->info)//Para isso basta verificar se o No a ser removido eh menor ou maior que o pai
                    ant->esq = remove_nodo(nodo); //Se menor o campo esquerdo ira apontar para o lugar que o No a ser removido estava
                else
                    ant->dir = remove_nodo(nodo);//e se maior o campo direito que vai apontar o lugar que o No a ser removido estava
            }

            printf("\n>Chave removida<\n"); //Feedback. Se isso ocorrer sera emitida a mensagem para o usuario
            return 1;
        }
        ant = nodo;
        if(valor < nodo->info)//incremento do while, tal qual a funcao de busca
            nodo = nodo->esq;
        else
            nodo = nodo->dir;
    }

    printf("\n>Chave nao encontrada<\n");//Se ele sair do while quer dizer que esta chave nao pertence a arvore
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////...REMOVER UM NO

//FUNCAO PARA RETORNAR A ALTURA DA ARVORE
int altura(Arvore *raiz)
{
    //Utilizamos basicamente a ideia do encaminhamento pos ordem recursivamente nesta funcao e na funcao "tamanho"
    //Se conseguimos imprimir os Nos conseguimos entao definir a altura da arvore e quantos tem
    int lado_esq, lado_dir;

    if(*raiz == NULL)//Se a raiz for NULL a altura sera 0
        return 0;

    //Chamamos recursivamente a funcao "altura" para subarvore esquerda e direita
    lado_esq = altura(&((*raiz)->esq));
    lado_dir = altura(&((*raiz)->dir));
    //Quando elas descerem no No folha a funcao retorna 0 e a medida que vai subindo(as ultimas chamadas feitas) eh contado +1 no retorno

    //no "final" sera retornado o lado que obteve maior numero
    if(lado_esq > lado_dir)// final entre aspas pois eh apenas o final de cada chamada recursiva que estamos nos referindo
        return (lado_esq + 1);
    else
        return (lado_dir + 1);

    //imagine o seguinte, temos um No que no momento esta sendo considerado a raiz e no seu lado esquerdo tem um numero que
    //representa uma altura e no lado direito outro, este if garante que ele pegue o que esta com a maior altura no momento

    //Por isso para melhor compreendimento, assim como dito nas funcoes de imprimir, levasse em consideracao que em algum momento cada No sera uma raiz
}

//FUNCAO PARA RETORNAR O TAMANHO DA ARVORE (quantidade de Nos)
int tamanho(Arvore *raiz)
{
    //Para o tamanho eh feita exatamente a mesma coisa
    int lado_esq, lado_dir;

    if(*raiz == NULL)
        return 0;

    lado_esq = tamanho(&((*raiz)->esq));
    lado_dir = tamanho(&((*raiz)->dir));

    //Soh que agora nao queremos o lado com maior numero, queremos a soma de ambos os lados. Pegamos a quantidade
    //de Nos de cada lado da sub-arvore e depois somamos tendo entao a quantidade total de Nos da arvore

    return (lado_dir + lado_esq + 1);
}
