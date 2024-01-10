#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    if (!head)
        return 0;

    node *tortoise = head;
    node *hare = head;
    while ((hare = hare->next) != NULL && (hare = hare->next) != NULL){
        tortoise = tortoise->next;

        if (tortoise == hare)
            return 1;
    }
    return 0;
}
