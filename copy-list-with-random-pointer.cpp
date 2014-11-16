/** 
* QUESTION:
*
* A linked list is given such that each node contains an additional random
* pointer which could point to any node in the list or null.
* 
* Return a deep copy of the list.
*
*/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        
        /*  Requires 3 Passes...
             
            First:  Make a copy of the source list where each dest
                    node's next pointer points to the corresponding
                    source's random node, and each source node's random
                    pointer points to the source node's corresponding dest
                    node.

            Second: Assign each dest node's random pointer to the
                    correct dest node by looking it up via dest->next->random.
                    Iterate through dest using src->random.

            Third:  Re-assign src node's random pointer to corresponding dest
                    node's next point. Then assign each dest node's next pointer to
                    the correct dest node by looking it up via src->next->random.
        */
    
        if (head == NULL)
            return (NULL);
        
        RandomListNode *src;
        RandomListNode *dest;

        // FIRST PASS

        src = head;

        while (src != NULL) {
            
            dest           = new RandomListNode(src->label);
            dest->next     = src->random;
            src->random    = dest;
            
            src            = src->next;
        }
        
        // SECOND PASS

        src = head;
        
        while(src != NULL) {
            
            dest = src->random;
            
            if (dest->next != NULL) {
                dest->random = dest->next->random;
            }
    
            src  = src->next;
        }
        
        // THIRD PASS

        RandomListNode *dest_head = head->random;
        
        src = head;
        dest = dest_head;
        
        while(src != NULL) {
            src->random = dest->next;

            if (src->next != NULL) {
                dest->next  = src->next->random;
            } else {
                dest->next = NULL;
            }
            
            src  = src->next;
            dest = dest->next;
        }
          
        return (dest_head);
    }
};