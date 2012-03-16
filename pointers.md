Pointers
========

You've probably heard countless times before that pointers are just addresses in memory.

That's about as useless as it gets, because the next question is, "Well, what do I do with an address of memory?"

So, let's start with a bit background. 

```c
void incr(int f) {
	f++;
}

int main (void) {
	int x = 0;
	incr(x);

	printf("%d\n", x);
	return 0;
}
```

If you actually ran this program, its prints 0.

But, why? I mean, you're calling the procedure `incr` on `x`, so, why doesn't it become 1?

Well, here's the issue. 

C doesn't pass in the variable `x`, it passes in the value contained inside `x`, and then wraps it up with the variable name `f` (not exactly, but, the analogy works in this case), so, when you increment `f`, that doesn't increment `x`. 

But, we want `x` to be incremented! How do we go about that?

One obvious solution, of course, is this:

```c
int incr(int f) {
	f++;
	return f;
} 

int main (void) {
	int x = 0;
	x = incr(x);
	printf("%d\n", x);
	return 0;
}
```

But, a much more interesting solution involves pointers. Here it is:

```c
void incr(int *f) {
	(*f)++;
}

int main (void) {
	int x = 0;
	incr(&x);

	printf("%d\n", x);
	return 0;
}
```

If you run this, we get the output we wanted!

But, what does this code mean?

First of all, notice the change in the definition of `incr`. It now has a parameter `int *f`. What that means is, instead of accepting an argument that's an integer, `incr` accepts an argument that's an address, and that address contains an integer.

Read that last sentence again. Now, once again. Okay, now we can move on.

Now, notice in the main function, that we no longer just call `incr(x)`, we call `incr(&x)`. That means that instead of just passing in the value of the integer `x`, we are passing in the address to the variable `x`.

Jump back in to the definition of `incr`. Notice that we don't just do `f++`, we actually do `(*f)++`. Let's break this apart. `*f` means to find the variable that resides at the address that is stored in `f` (often called **dereferencing**). 

Read that last sentence again.

So, `(*f)++` means to take that variable, and increment it!

So, what we're doing is, taking the address of `x`, passing it in to `incr`, which then takes that address, finds the variable at that address and increments that variable (or, you can think of it as incrementing the value inside the block of memory at that address, which would be more accurate in some respects).

Awesome!

But, why would anyone go through all of that, can't you just return the value?

Yes, you can, but, this is just a stepping stone into the world of pointers.

For example, what if you had some large data structure that you needed to pass into a procedure, perform some operation on that structure? If you used the return-ing method, you'd have to pass in that large data structure into your function, if you used pointers, you'd just be passing around an address (which would be much smaller). 

Let's make a little jump for a moment (don't read the following if you haven't learned about arrays yet). 

```c
void changeFirst(int x[]) {
	x[0] = 14;
}

int main (void) {
	int x[] = {1, 2, 3, 4};
	changeFirst(x);
	
	printf("%d\n", x[0]);
}
```
If you ran that, something pretty amazing happened. `x[0]` actually changed to 14.

But, wait, why did that happen? When we tried that with `int`s, the value didn't change!

Brace yourself.

When we declare `int x[]`, `x` actually became a pointer. What happens is, a little bit of memory is reserved for that array, and `x` is made to contain the address at the beginning of the array!

There's all kinds of other things that are possible with this.

```c 
void squareFourth(int x[]) {
	x[3] = x[3] * x[3];
} 

int main (void) {
	int x[] = {1, 2, 3, 4, 5}
	
	squareFourth(x);
	
	printf("%d\n", x[3]);
}
```

Which will print 16. 

An interesting way to write this code would to use pointer notation:

```c
void squareFourth(int *x) {
	*(x+3) = *(x+3) * (*(x+3));
}

int main (void) {
	int x[] = {1, 2, 3, 4, 5};
	
	squareFourth(x);

	printf("%d\n", x[3]);
	return 0;
}
```

The code looks a bit complicated, but, let's break into pieces.

The only new part that we're encountering is this line:

```c
*(x+3) = *(x+3) * (*(x+3))
```

So, first of all, x is a pointer, right? So, what happens when you add three to a pointer?

This is one of C's specialities. It doesn't just move ahead three units in memory; it moves ahead three integer sizes ahead in memory.

What does that mean? 

That means that when you add three to a pointer, its the same thing as doing x[3]! 

So, when we do `*(x+3)`, we're saying "find the variable/thing stored in memory at the address x, plus three integer widths", or 'x[3]'. The right side is just taking that and squaring it.

That's it!

Pointers allow you to do all kinds of cool juggling with arrays and such, and you can pass around a pointer instead of a data structure, making stuff much easier to deal with.

And, once you learn about heaps, pointers allow to keep track of memory stored on the heap.

