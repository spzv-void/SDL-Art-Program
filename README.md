# SDL Art Program
Simple SDL program that allows the user to draw on an empty white canvas. Clone, compile, and run.
![Showcase drawing of the program](showcase)

Small hobby project, feel free to submit pull requests or use in your own projects; i'm ok with anything.
__________________________________________________________________________
## Keybinds
**Colors**

*R - Change brush to red*

*B - Change brush to blue*

*V - Change brush to black*


You can add your own custom colors by pasting this into the last part of InitSDL where there are a lot of switch cases:
```C
case SDL_SCANCODE_(your input of choice, must be capital if a letter):
        brushColor = (SDL_Color){R, G, B, A};
        break;
```

**Brush Size**

*H - Increase brush size*

*L - Decrease brush size*



would add an eraser and undo feature but i am stupid. maybe later
