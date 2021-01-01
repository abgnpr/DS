#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define flush() while (getchar() != '\n')

#if defined _WIN32
#define clear() system("cls")
#elif defined unix
#define clear() system("clear")
#endif

char get_choice()
{
    char choice;
    scanf("%c", &choice);
    flush();
    return choice;
}

void pause()
{
    printf("\n\nPress enter to continue...\n");
    flush();
}

#define success 1
#define failure 0

// Node to hold a term of a polynomial
typedef struct Term
{
    int exp, // exponent
        coe; // coefficient
    struct Term *next;
} Term;

// receives exponent and coefficient for a term
Term *getTerm()
{
    Term *t = malloc(sizeof *t);

    printf("Exponent?    : ");
    scanf("%d", &t->exp);
    flush();

    if (t->exp < 0)
        return NULL;

    printf("Coefficient? : ");
    scanf("%d", &t->coe);
    flush();

    return t;
}

// Queue to represent a polynomial (queue of terms)
typedef struct Queue
{
    Term *head, *tail;
    char name;
} Queue, Polynomial;

#define _1st_Term(q) (*q.head)

// returns true if q is empty
#define is_empty(q) ((q).head == NULL ? true : false)

// enqueues a term into the polynomial
int enqueue(Queue *q, Term *t)
{
    if (is_empty(*q))
    {
        q->head = q->tail = t;
        return success;
    }

    if (t->exp >= q->tail->exp) // doubt
        return failure;

    // else
    q->tail->next = t;
    q->tail = t;
    return success;
}

// dequeues a term from the polynomial
// and returns it; doesn't deallocate
Term *dequeue(Queue *q)
{
    if (is_empty(*q))
        return NULL;

    Term *dequeued = q->head;

    if (q->head == q->tail)
        q->head = q->tail = NULL;
    else
        q->head = q->head->next;

    return dequeued;
}

char polyName = 'A';
#define newPolyName() (polyName == 'R' ? ++polyName : polyName++)

// creates a new polynomial by taking terms as input
Polynomial inputPolynomial()
{
    Queue q = {NULL, NULL, newPolyName()};

    printf("\nEnter polynomial %c\n", q.name);

    printf("\nInput a term (enter -ve exponent to finish input)\n------------\n");
    do
    {
        Term *t = getTerm();
        if (!t || !enqueue(&q, t))
            break;
        printf("\nInput next term (enter -ve exponent to finish input)\n---------------\n");
    } while (true);

    printf("\n");

    return q;
}

// returns the order of the polynomial
#define order(p) (is_empty(p) ? -1 : _1st_Term(p).exp)

// shows the polynomial
void showPolynomial(Polynomial p)
{
    printf("\n%c = ", p.name);

    if (is_empty(p))
        printf("nil");

    for (bool firstTime = true; !is_empty(p); firstTime = false)
    {
        if (firstTime)
            printf("%d_x%d", _1st_Term(p).coe, _1st_Term(p).exp);
        else
            printf(" %c %d_x%d", (_1st_Term(p).coe >= 0 ? '+' : '-'), abs(_1st_Term(p).coe), _1st_Term(p).exp);
        dequeue(&p);
    }

    printf("\n");
}

void reset(Polynomial p)
{
    while (!is_empty(p))
        free(dequeue(&p));
}

// adds a and b
Polynomial add(Polynomial a, Polynomial b)
{
    Polynomial r = {NULL, NULL, 'R'}; // to store result

    while (!is_empty(a) && !is_empty(b))
    {
        Term *t = malloc(sizeof *t);

        if (_1st_Term(a).exp > _1st_Term(b).exp)
        {
            t->exp = _1st_Term(a).exp;
            t->coe = _1st_Term(a).coe;
            dequeue(&a);
        }
        else if (_1st_Term(a).exp < _1st_Term(b).exp)
        {
            t->exp = _1st_Term(b).exp;
            t->coe = _1st_Term(b).coe;
            dequeue(&b);
        }
        else
        {
            t->exp = _1st_Term(a).exp;
            t->coe = _1st_Term(a).coe + _1st_Term(b).coe;
            dequeue(&a);
            dequeue(&b);
        }

        enqueue(&r, t);
    }

    Polynomial rem = !is_empty(a) ? a : b;

    while (!is_empty(rem))
    {
        Term *t = malloc(sizeof *t);
        *t = _1st_Term(rem);
        enqueue(&r, t);
        dequeue(&rem);
    }

    return r;
}

// subtracts b from a
Polynomial subtract(Polynomial a, Polynomial b)
{
    Polynomial b_ = {NULL, NULL};

    while (!is_empty(b))
    {
        Term *t = malloc(sizeof *t);
        t->coe = -(_1st_Term(b).coe);
        t->exp = _1st_Term(b).exp;
        enqueue(&b_, t);
        dequeue(&b);
    }

    Polynomial r = add(a, b_);
    reset(b_);
    return r;
}

// multiply a and b
Polynomial multiply(Polynomial a, Polynomial b)
{
    Polynomial r = {NULL, NULL, 'R'}; // to store result

    while (!is_empty(a))
    {
        Polynomial b_ = b;
        while (!is_empty(b_))
        {
            Term *t = malloc(sizeof *t);
            t->coe = _1st_Term(a).coe * _1st_Term(b_).coe;
            t->exp = _1st_Term(a).exp + _1st_Term(b_).exp;
            if (!enqueue(&r, t))
            {
                Polynomial tmp = {NULL, NULL, 'R'};
                bool inserted = false; // flag
                while (!is_empty(r))
                {
                    if (inserted)
                        enqueue(&tmp, dequeue(&r));
                    else
                    {
                        if (t->exp == _1st_Term(r).exp)
                        {
                            _1st_Term(r).coe += t->coe;
                            free(t);
                            inserted = true;
                        }
                        else if (t->exp > _1st_Term(r).exp)
                        {
                            enqueue(&tmp, t);
                            inserted = true;
                        }
                        else
                            enqueue(&tmp, dequeue(&r));
                    }
                }

                r = tmp;
            }
            dequeue(&b_);
        }
        dequeue(&a);
    }

    return r;
}

int evaluate(Polynomial p)
{
    int x, r = 0;

    printf("\nEnter x: ");
    scanf("%d", &x);
    flush();

    while (!is_empty(p))
    {
        r += _1st_Term(p).coe * (int)pow(x, _1st_Term(p).exp);
        dequeue(&p);
    }

    return r;
}

void main(void)
{
    clear();
    Polynomial a = inputPolynomial(), b, result;

    bool done = false;
    do
    {
        clear();

        printf("\n\
    1 -- Add two polynomials\n\
    2 -- Subtract one polynomial from other\n\
    3 -- Multiply two polynomial\n\
    4 -- Evaluate a polynomial\n\
    5 -- Order of the polynomial\n\
    6 -- Reset a polynomial\n\
    7 -- Display the polynomial\n\
    q -- quit\n\
    \n\
    >>> ");
        switch (get_choice())
        {
        case '1': // add
            clear();
            b = inputPolynomial();
            clear();
            result = add(a, b);
            showPolynomial(a);
            showPolynomial(b);
            showPolynomial(result);
            pause();
            reset(b);
            reset(result);
            break;
        case '2': // subtract
            clear();
            b = inputPolynomial();
            clear();
            result = subtract(a, b);
            showPolynomial(a);
            showPolynomial(b);
            showPolynomial(result);
            pause();
            reset(b);
            reset(result);
            break;
        case '3': // product
            clear();
            b = inputPolynomial();
            clear();
            result = multiply(a, b);
            showPolynomial(a);
            showPolynomial(b);
            showPolynomial(result);
            pause();
            reset(b);
            reset(result);
            break;
        case '4': // evaulate
            clear();
            showPolynomial(a);
            printf("\nResult = %d\n", evaluate(a));
            pause();
            break;
        case '5': // order
            clear();
            showPolynomial(a);
            printf("\nOrder of %c: %d\n", a.name, order(a));
            pause();
            break;
        case '6': // reset
            reset(a);
            clear();
            a = inputPolynomial(); // necessary
            break;
        case '7': // show
            clear();
            showPolynomial(a);
            pause();
            break;
        case 'q': // quit
            reset(a);
            done = true;
            break;
        }
    } while (!done);
}
