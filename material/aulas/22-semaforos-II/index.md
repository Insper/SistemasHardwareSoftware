# 22 - Semáforos II e Modelos de concorrência

Na aula anterior, trabalhamos com semáforos de um ponto de vista principalmente conceitual.

Aproveitaremos a aula de hoje para fixar nosso conhecimento sobre semáforos, verificando como implementar semáforos POSIX. Além disso, iremos explorar o modelo produtor consumidor.

## Correção Rendez-vous POSIX

Implemente (do zero) um programa que cria duas threads e as sincroniza usando *RDV*. Ambas deverão fazer um `print` antes e um depois do ponto de encontro. Use o seguinte esquema como guia.

![Tarefas sincronizadas usando um RDV](rdv.svg)

As partes A e B podem ser feitas em qualquer ordem, mas ambas obrigatoriamente devem ocorrer antes de iniciar a execução de C e D. Note que C e D também podem ser feitas em qualquer ordem.

```c
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    sem_t *s1, *s2;
} t_arg;

void *thread1(void *_arg) {
    t_arg *arg = _arg;

    printf("A\n");
    sem_post(arg->s1);
    sem_wait(arg->s2);    
    printf("C\n");

    return NULL;
}

void *thread2(void *_arg) {
    t_arg *arg = _arg;
    
    printf("B\n");
    sem_post(arg->s2);
    sem_wait(arg->s1);
    printf("D\n");

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t *tid = malloc(sizeof(pthread_t) * 2);

    t_arg *arg = malloc(sizeof(t_arg));
    
    sem_t *s1 = malloc(sizeof(sem_t));
    sem_t *s2 = malloc(sizeof(sem_t));

    sem_init(s1, 0, 0);
    sem_init(s2, 0, 0);

    arg->s1 = s1;
    arg->s2 = s2;
    
    pthread_create(&tid[0], NULL, thread1, arg);

    pthread_create(&tid[1], NULL, thread2, arg);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    sem_destroy(s1);
    sem_destroy(s2);

    free(tid);
    free(s1);
    free(s2);
    free(arg);
    
    return 0;
}
```

## Aplicação de Semáforos

Já vimos o uso de semáforos para sincronizar threads, de forma que as threads esperem pelas outras em um ponto de encontro. Agora, vamos utilizar semáforos para controlar a quantidade de threads que podem acessar ao mesmo tempo um recurso computacional.

!!! example
    Implemente (do zero) um programa que cria `N` threads, entretanto, apenas `MAX` threads podem executar ao mesmo tempo.

!!! tip
    Tente pensar no que acontece com `sem_wait` e `sem_post` quando o semáforo é inicializado com valor maior que zero.

## Modelos de concorrência

Vamos implementar o modelo produtor consumidor, levando em consideração que:

1. As threads produtoras e consumidoras compartilham um cache único. Pode ser um array de inteiros.
2. Ambas as threads rodam em loop infinito simulando um stream de dados. A cada iteração, as threads sorteiam um valor aleatório de segundos (por ex, entre `0` e `5`) e então tentam pruduzir / consumir os dados.

!!! example
    Implemente (do zero) um programa que cria uma thread produtora e uma thread consumidora.

![Modelo com uma thread produtora e uma thread consumidora](produtor_consumidor1.png)


!!! exercise text short
    Como os índices do cache serão manipulados pelas threads produtora e consumidora?! Qual tipo de dados é indicado?

    !!! answer "Resposta"
        Procure por fila circular, buffer circular!

!!! exercise text short
    Como podemos controlar para que a thread produtora espere caso o buffer esteja cheio?

    !!! answer "Resposta"
        Podemos utilizar um semáforo inicializado com o tamanho no buffer. Cada produção realiza um wait neste semáforo. Quando o semáforo zera então o cache está cheio e a thread produtora deve esperar. Tente pensar se o consumo deve ou não atualizar este semáforo!

!!! exercise text short
    Como podemos controlar para que a thread consumidora espere caso o buffer esteja vazio?

    !!! answer "Resposta"
        Podemos utilizar um semáforo inicializado com zero. Quando a thread produtora produz algo, este semáforo recebe um post. Tente pensar se o consumo deve ou não atualizar este semáforo!

!!! example
    Implemente uma versão com `M` threads produtoras e `N` threads consumidoras.

![Modelo com `M` threads produtoras e `N` threads consumidoras](produtor_consumidor2.png)
