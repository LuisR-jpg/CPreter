# CPreter
##### Competitive Programming Interpreter
###### Have you ever wanted to code a quick idea? That's what CPreter was made for!

### How to code?
In order to get started, you can run the next bunch of lines in charged of guessing a number you think.

    fp "Piensa en un numero del 0 al 1000"
    di numero = 500, ini = 0, fin = 1000
    db adivine = 0, may
    cw !adivine
        numero = (ini + fin)/2
        fp "El numero que pensaste es: ", numero, "?"
        fr adivine
        si !adivine
            fp "El numero que piensas es mayor?"
            fr may
            si may
                ini = numero
            se 
                fin = numero
    fp "I won"

For more information, refer yourself to the [syntax table](https://github.com/LuisR-jpg/CPreter/blob/main/Syntax%20Table.pdf).
Or you can see more [examples](https://github.com/LuisR-jpg/CPreter/tree/main/Codes).


### How to run it?
1. Make sure you have this repo in your files.
2. Compile the ***Master.cpp*** file in your console.
3. To run; execute the ***.exe*** generated after compiling and add the name of the file containing your *CPreter code*.
    > myCode.exe HelloWorld.cpr

    *Optional: Add the word *debug* in the arguments to see what every stage of the inner code does.

