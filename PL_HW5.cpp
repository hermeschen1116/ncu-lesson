#include <iostream>

using namespace std;
typedef struct card_t {
	int number;
	char suit;
} card_t;

typedef struct card_node {
	card_t card;
    struct card_node *pair;
	struct card_node *next;
} node;

void getCard(char const input[], char *suit, int *number);
node *newNode(char suit, int number);
node *push(node *stack, char suit, int number);
node *pop(node *stack);
node *search(node *cards, node *input);
node *insert(node *cards, node *input);
node *searchPair(node *stack);
void remove(node *cards);
void show(node *cards);
void clear(node *head);

int main() {
    char input[3];
    char suit;
    int number, cnt = 0;
	node *stack = nullptr, *cards = nullptr, *tmp, *pick;
	
	while (cin >> input && cnt < 13) {
        getCard(input, &suit, &number);
        stack = push(stack, suit, number);
        cnt++;
    }

    tmp = stack;
    while (tmp != nullptr) {
        pick = newNode(stack->card.suit, stack->card.number);
        stack = pop(stack);
        cards = insert(cards, pick);
        tmp = tmp->next;
    }

    remove(cards);
    show(cards);
    clear(stack);
    clear(cards);
	
	return 0;
}

void getCard(char const input[], char *suit, int *number) {
    *suit = input[0];
    if (input[2] == '\0') *number = input[1] - 48;
    else *number = input[1] * 10 + input[2] - 528;
}

node *newNode(char suit, int number) {
    node *tmp = new node;

    tmp->card.suit = suit;
    tmp->card.number = number;
    tmp->pair = nullptr;
    tmp->next = nullptr;

    return tmp;
}

node *push(node *stack, char suit, int number) {
	node *input = newNode(suit, number);
	if (stack != nullptr) input->next = stack;

    return input;
}

node *pop(node *stack) {
    node *tmp = stack;

    if (stack != nullptr) {
        stack = stack->next;
        delete tmp;
    }

    return stack;
}

node *search(node *cards, node *input) {
    node *cur = cards, *next = cur->next;

    while (next != nullptr) {
        if (input->card.number < next->card.number) break;
        if (input->card.number == next->card.number && input->card.suit < next->card.suit) {
            input->pair = next;
            break;
        }
        cur = next;
        next = next->next;
    }

    return cur;
}

node *insert(node *cards, node *input) {
    node *target;

    if (cards == nullptr) cards = input;
    else {
        target = search(cards, input);
        if (target->next != nullptr) input->next = target->next;
        target->next = input;
    }

    return cards;
}

node *searchPair(node *stack) {
    node *tmp = stack;

    while (tmp != nullptr) {
        if (tmp->pair != nullptr) break;
        tmp = tmp->next;
    }

    return tmp;
}

void remove(node *cards) {
    node *cur = cards, *target;

    while (cur != nullptr) {
        target = searchPair(cur);
        if (target != nullptr) {
            cur->next = target->pair->next;
            delete target->pair;
            delete target;
        } else break;
        cur = cur->next;
    }
}

void show(node *cards) {
    node *cur = cards;

    while (cur != nullptr) {
        cout << cur->card.suit << cur->card.number << endl;
        cur = cur->next;
    }
}

void clear(node *head) {
    node *tmp;
    while (head != nullptr) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}
