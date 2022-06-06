// Structure to temporarily store needed values just before adding this (aMove) structure to the stack array
struct aMove
{
    // row
    int row;
    // column
    int column;
    // new value
    int nv;
    // old value
    int ov;
};
// Structure that allows stack implementation
struct stack
{
    struct aMove *array;
    int top;
};

// Declaring structures
struct stack s;
struct aMove t;

// Function to initialize the stack with size "size", allocates a memory block with malloc()
void init_stack(struct stack *s, int size)
{
    s->array = (struct aMove *)malloc((size + 1) * sizeof(struct aMove));
    s->top = -1;
}
// Function to push onto the stack a structure "m", automatically increases the size of the stack array through realloc()
void push(struct stack *s, struct aMove *m)
{
    if (s->top == MAX - 1)
    {
        // Increase the size of the stack array by 10
        MAX += 10;
        s->array = realloc(s->array, (MAX * sizeof(struct aMove)));
    }
    s->top++;
    s->array[s->top] = *m;
}
// Function to remove an item from the stack
void pop(struct stack *s)
{
    if (s->top == -1)
    {
        printf("Stack is empty\n");
        return;
    }
    s->top--;
}