#include"sr.h"
#include"que.h"
int que_init(pQue t,int capacity)
{
    t->size=0;
    t->capacity=capacity;
    t->head=t->tail=NULL;
    int ret=pthread_mutex_init(&t->mutex,NULL);
    ERROR_CHECK(ret,-1,"pthread_mutex_init")
    return 0;
}

int que_insert(pQue t,int fd)
{
    if(t->size<t->capacity){
        if(NULL==t->head){
            t->head=(pque_node)calloc(1,sizeof(que_node));
            t->tail=t->head;
            t->head->fd=fd;
        }else{
            t->tail->next=(pque_node)calloc(1,sizeof(que_node));
            t->tail=t->tail->next;
            t->tail->fd=fd;
        }
        t->size++;
        return 0;
    }else{
        printf("que is full\n");
        return -1;
    }
}
//fd是传出参数
int que_get(pQue t,int* fd)
{
    if(0==t->size){
        return -1;
    }
    pque_node p=t->head;
    t->head=t->head->next;
    *fd=p->fd;
    free(p);
    t->size--;
    return 0;
}
//net版insert
int que_insert_n(pQue t,pque_node d)
{
    if(t->size<t->capacity){
        if(NULL==t->head||NULL==t->tail){
            t->head=(pque_node)calloc(1,sizeof(que_node));
            //出问题，字符串变化,血坑，申请空间踩到
            t->tail=t->head;
            t->head->fd=d->fd;
            t->head->code=d->code;
            t->head->req=d->req;
            t->head->user_id=d->user_id;
            strcpy(t->head->file_name,d->file_name);
            memcpy(&t->head->addr,&d->addr,sizeof(t->head->addr));
        }else{
            t->tail->next=(pque_node)calloc(1,sizeof(que_node));
            t->tail=t->tail->next;
            t->tail->fd=d->fd;
            t->tail->code=d->code;
            t->tail->req=d->req;
            t->tail->user_id=d->user_id;
            strcpy(t->head->file_name,d->file_name);
            memcpy(&t->tail->addr,&d->addr,sizeof(t->head->addr));
        }
        t->size++;
        LOG3("que里面:",t->tail->file_name);
        return 0;
    }else{
        printf("que is full\n");
        return -1;
    }
}
//d是传出参数，是队列节点类型
int que_get_n(pQue t,pque_node d)
{
    if(0==t->size){
        return -1;
    }
    pque_node p=t->head;
    t->head=t->head->next;
    d->req=p->req;
    d->code=p->code;
    d->fd=p->fd;
    d->user_id=p->user_id;
    memcpy(d->file_name,p->file_name,strlen(p->file_name));
    memcpy(&d->addr,&p->addr,sizeof(p->addr));
    d->next=NULL;
    free(p);
    t->size--;
    return 0;
}
// int qgets_insert_n(pQgets t,pgets_node d)
// {
//     if(t->size<t->capacity){
//         if(NULL==t->head||NULL==t->tail){
//             t->head=(pgets_node)calloc(1,sizeof(gets_node));
//             //出问题，字符串变化,血坑，申请空间踩到
//             t->tail=t->head;
//             t->head->fd=d->fd;
//             t->head->fd=d->fd;
//             t->head->p=d->p;
//         }else{
//             t->tail->next=(pgets_node)calloc(1,sizeof(gets_node));
//             t->tail=t->tail->next;
//             t->tail->fd=d->fd;
//             t->tail->p=d->p;
//         }
//         t->size++;
//         return 0;
//     }else{
//         printf("gets_que is full\n");
//         return -1;
//     }
// }

// //d是传出参数，是队列节点类型
// int qgets_get_n(pQgets t,pgets_node d)
// {
//     if(0==t->size){
//         return -1;
//     }
//     pgets_node p=t->head;
//     t->head=t->head->next;
//     d->fd=p->fd;
//     d->p=d->p;
//     d->next=NULL;
//     free(p);
//     t->size--;
//     return 0;
// }
// int qgets_init(pQgets t,int capacity)
// {
//     t->size=0;
//     t->capacity=capacity;
//     t->head=t->tail=NULL;
//     int ret=pthread_mutex_init(&t->mutex,NULL);
//     ERROR_CHECK(ret,-1,"pthread_mutex_init")
//     return 0;
// }