#include <iostream>

using namespace std;

typedef struct card_t {
	int number;
	char suit;
} card_t;

typedef struct card_node {
	card_t card;
	struct card_node *next;
} node;

void getCard(char const input[], char *suit, int *number);
node *newNode(char suit, int number);
node *push(node *stack, char suit, int number);
node *pop(node *stack);
bool nodeCompare(node *n1, node *n2);
node *search(node *cards, node *input);
node *insert(node *cards, node *input);
bool isPair(node *card);
node *remove2(node *card1);
node *removePairs(node *cards);
void show(node *cards);
void clear(node *head);

int main() {
    char input[3];
    char suit;
    int number, cnt = 0;
	node *stack = nullptr, *cards = nullptr, *pick;
	
	while (cin >> input && cnt < 13) {
        getCard(input, &suit, &number);
        stack = push(stack, suit, number);
        cnt++;
    }

    while (stack != nullptr) {
        pick = newNode(stack->card.suit, stack->card.number);
        stack = pop(stack);
        cards = insert(cards, pick);
    }

    cards = removePairs(cards);
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

bool nodeCompare(node *n1, node *n2) {
    if (n1->card.number < n2->card.number)  return false;
    if (n1->card.number == n2->card.number && n1->card.suit < n2->card.suit) return false;
    return true;
}

node *search(node *cards, node *input) {
    node *pre = nullptr, *cur = cards;

    while (cur != nullptr) {
        if (!nodeCompare(input, cur)) break;
        pre = cur;
        cur = cur->next;
    }

    return pre;
}

node *insert(node *cards, node *input) {
    node *target;

    if (cards == nullptr) cards = input;
    else {
        target = search(cards, input);
        if (target == nullptr) {
            input->next = cards;
            cards = input;
        } else {
            if (target->next != nullptr) input->next = target->next;
            target->next = input;
        }
    }

    return cards;
}

bool isPair(node *card) {
    node *nextCard = card->next;

    if (nextCard != nullptr && nextCard->card.number == card->card.number) return true;
    return false;
}

node *remove2(node *card1) {
    node *card2 = card1->next, *card3 = nullptr;

    if (card2 != nullptr) {
        if (card2->next != nullptr) card3 = card2->next;
        delete card2;
        delete card1;
    }

    return card3;
}

node *removePairs(node *cards) {
    node *pre = cards, *cur = cards;

    if (cards != nullptr) {
        while (cur != nullptr) {
            if (isPair(cur)) {
                if (cur == cards) {
                    cards = remove2(cards);
                    pre = cards;
                    cur = pre;
                } else {
                    pre->next = remove2(cur);
                    if (pre->next != nullptr) cur = pre->next;
                }
            } else {
                pre = cur;
                cur = cur->next;
            }
        }
    }

    return cards;
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
