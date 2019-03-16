/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->q_size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    while (q->head) {
        list_ele_t *temp = q->head;
        q->head = q->head->next;
        free(temp->value);
        // free(temp->next);
        free(temp);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* Check input q & s address */
    if (q == NULL || s == NULL)
        return false;

    /* Memory allocation for list_ele_t and check address */
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        free(newh);
        return false;
    }

    /* Memory allocation for list_ele_t->value and check address */
    newh->value = malloc(sizeof(char) * strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh->value);
        free(newh);
        return false;
    }

    /* Set initial value for newh->value */
    memset(newh->value, (int) '\0', sizeof(char) * strlen(s) + 1);
    strcpy(newh->value, s);

    /* Check empty queue or not */
    if (q->head == NULL) {
        q->head = newh;
        q->tail = newh;
        newh->next = NULL;
        ++q->q_size;
        return true;
    } else {
        newh->next = q->head;
        q->head = newh;
        ++q->q_size;
        return true;
    }
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Check input q & s address */
    if (q == NULL || s == NULL)
        return false;

    /* Memory allocation for list_ele_t and check address */
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        free(newt);
        return false;
    }

    /* Memory allocation for list_ele_t->value and check address */
    newt->value = malloc(sizeof(char) * strlen(s) + 1);
    if (newt->value == NULL) {
        free(newt->value);
        free(newt);
        return false;
    }
    /* Set initial value for newh->value */
    memset(newt->value, (int) '\0', sizeof(char) * strlen(s) + 1);
    strcpy(newt->value, s);
    newt->next = NULL;

    /* Check empty queue or not */
    if (q->head == NULL) {
        q->head = newt;
        q->tail = newt;
        ++q->q_size;
        return true;
    } else {
        q->tail->next = newt;
        q->tail = newt;
        ++q->q_size;
        return true;
    }
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* Check queue is NULL or empty */
    if (q == NULL || q->head == NULL || sp == NULL)
        return false;

    memset(sp, (int) '\0', bufsize);
    strncpy(sp, q->head->value, bufsize - 1);
    list_ele_t *temp;
    temp = q->head;
    q->head = q->head->next;
    free(temp->value);
    //  free(temp->next);
    free(temp);
    --q->q_size;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->head == NULL)
        return 0;
    else
        return q->q_size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL)
        return;
    list_ele_t *temp = q->head->next;
    q->tail = q->head;
    while (temp) {
        q->tail->next = temp->next;
        temp->next = q->head;
        q->head = temp;
        temp = q->tail->next;
    }
}
