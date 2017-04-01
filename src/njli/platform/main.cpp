/*
 *  rectangles.c
 *  written by Holmes Futrell
 *  use however you want
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "SDL.h"
#include "Game.h"

#if defined(__PSP__)
#define DEFAULT_WINDOW_WIDTH  480
#define DEFAULT_WINDOW_HEIGHT 272
#else
#define DEFAULT_WINDOW_WIDTH  640
#define DEFAULT_WINDOW_HEIGHT 480
#endif

#define VERBOSE_VIDEO   0x00000001
#define VERBOSE_MODES   0x00000002
#define VERBOSE_RENDER  0x00000004
#define VERBOSE_EVENT   0x00000008
#define VERBOSE_AUDIO   0x00000010

#define VIDEO_USAGE \
"[--video driver] [--renderer driver] [--gldebug] [--info all|video|modes|render|event] [--log all|error|system|audio|video|render|input] [--display N] [--fullscreen | --fullscreen-desktop | --windows N] [--title title] [--icon icon.bmp] [--center | --position X,Y] [--geometry WxH] [--min-geometry WxH] [--max-geometry WxH] [--logical WxH] [--scale N] [--depth N] [--refresh R] [--vsync] [--noframe] [--resize] [--minimize] [--maximize] [--grab] [--allow-highdpi]"

#define AUDIO_USAGE \
"[--rate N] [--format U8|S8|U16|U16LE|U16BE|S16|S16LE|S16BE] [--channels N] [--samples N]"

typedef struct
{
    /* SDL init flags */
    char **argv;
    Uint32 flags;
    Uint32 verbose;
    
    /* Video info */
    const char *videodriver;
    int display;
    const char *window_title;
    const char *window_icon;
    Uint32 window_flags;
    int window_x;
    int window_y;
    int window_w;
    int window_h;
    int window_minW;
    int window_minH;
    int window_maxW;
    int window_maxH;
    int logical_w;
    int logical_h;
    float scale;
    int depth;
    int refresh_rate;
    int num_windows;
    SDL_Window **windows;
    
    /* Renderer info */
    const char *renderdriver;
    Uint32 render_flags;
    SDL_bool skip_renderer;
    SDL_Renderer **renderers;
    SDL_Texture **targets;
    
    /* Audio info */
    const char *audiodriver;
    SDL_AudioSpec audiospec;
    
    /* GL settings */
    int gl_red_size;
    int gl_green_size;
    int gl_blue_size;
    int gl_alpha_size;
    int gl_buffer_size;
    int gl_depth_size;
    int gl_stencil_size;
    int gl_double_buffer;
    int gl_accum_red_size;
    int gl_accum_green_size;
    int gl_accum_blue_size;
    int gl_accum_alpha_size;
    int gl_stereo;
    int gl_multisamplebuffers;
    int gl_multisamplesamples;
    int gl_retained_backing;
    int gl_accelerated;
    int gl_major_version;
    int gl_minor_version;
    int gl_debug;
    int gl_profile_mask;
} SDLTest_CommonState;







static void
SDLTest_CommonQuit(SDLTest_CommonState * state)
{
    int i;
    
    njli::NJLIGameEngine::destroy();
    
    SDL_free(state->windows);
    if (state->targets) {
        for (i = 0; i < state->num_windows; ++i) {
            if (state->targets[i]) {
                SDL_DestroyTexture(state->targets[i]);
            }
        }
        SDL_free(state->targets);
    }
    if (state->renderers) {
        for (i = 0; i < state->num_windows; ++i) {
            if (state->renderers[i]) {
                SDL_DestroyRenderer(state->renderers[i]);
            }
        }
        SDL_free(state->renderers);
    }
    if (state->flags & SDL_INIT_VIDEO) {
        SDL_VideoQuit();
    }
    if (state->flags & SDL_INIT_AUDIO) {
        SDL_AudioQuit();
    }
    SDL_free(state);
    SDL_Quit();
}

static void
SDLTest_ScreenShot(SDL_Renderer *renderer)
{
    SDL_Rect viewport;
    SDL_Surface *surface;
    
    if (!renderer) {
        return;
    }
    
    SDL_RenderGetViewport(renderer, &viewport);
    surface = SDL_CreateRGBSurface(0, viewport.w, viewport.h, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
                                   0x00FF0000, 0x0000FF00, 0x000000FF,
#else
                                   0x000000FF, 0x0000FF00, 0x00FF0000,
#endif
                                   0x00000000);
    if (!surface) {
        fprintf(stderr, "Couldn't create surface: %s\n", SDL_GetError());
        return;
    }
    
    if (SDL_RenderReadPixels(renderer, NULL, surface->format->format,
                             surface->pixels, surface->pitch) < 0) {
        fprintf(stderr, "Couldn't read screen: %s\n", SDL_GetError());
        SDL_free(surface);
        return;
    }
    
    if (SDL_SaveBMP(surface, "screenshot.bmp") < 0) {
        fprintf(stderr, "Couldn't save screenshot.bmp: %s\n", SDL_GetError());
        SDL_free(surface);
        return;
    }
}

static const char *
ControllerAxisName(const SDL_GameControllerAxis axis)
{
    switch (axis)
    {
#define AXIS_CASE(ax) case SDL_CONTROLLER_AXIS_##ax: return #ax
            AXIS_CASE(INVALID);
            AXIS_CASE(LEFTX);
            AXIS_CASE(LEFTY);
            AXIS_CASE(RIGHTX);
            AXIS_CASE(RIGHTY);
            AXIS_CASE(TRIGGERLEFT);
            AXIS_CASE(TRIGGERRIGHT);
#undef AXIS_CASE
        default: return "???";
    }
}

static const char *
ControllerButtonName(const SDL_GameControllerButton button)
{
    switch (button)
    {
#define BUTTON_CASE(btn) case SDL_CONTROLLER_BUTTON_##btn: return #btn
            BUTTON_CASE(INVALID);
            BUTTON_CASE(A);
            BUTTON_CASE(B);
            BUTTON_CASE(X);
            BUTTON_CASE(Y);
            BUTTON_CASE(BACK);
            BUTTON_CASE(GUIDE);
            BUTTON_CASE(START);
            BUTTON_CASE(LEFTSTICK);
            BUTTON_CASE(RIGHTSTICK);
            BUTTON_CASE(LEFTSHOULDER);
            BUTTON_CASE(RIGHTSHOULDER);
            BUTTON_CASE(DPAD_UP);
            BUTTON_CASE(DPAD_DOWN);
            BUTTON_CASE(DPAD_LEFT);
            BUTTON_CASE(DPAD_RIGHT);
#undef BUTTON_CASE
        default: return "???";
    }
}

static void
SDLTest_PrintEvent(SDL_Event * event)
{
    if ((event->type == SDL_MOUSEMOTION) || (event->type == SDL_FINGERMOTION)) {
        /* Mouse and finger motion are really spammy */
        return;
    }
    
    switch (event->type) {
        case SDL_WINDOWEVENT:
            switch (event->window.event) {
                case SDL_WINDOWEVENT_SHOWN:
                    SDL_Log("SDL EVENT: Window %d shown", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    SDL_Log("SDL EVENT: Window %d hidden", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    SDL_Log("SDL EVENT: Window %d exposed", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_MOVED:
                    SDL_Log("SDL EVENT: Window %d moved to %d,%d",
                            event->window.windowID, event->window.data1,
                            event->window.data2);
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    SDL_Log("SDL EVENT: Window %d resized to %dx%d",
                            event->window.windowID, event->window.data1,
                            event->window.data2);
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    SDL_Log("SDL EVENT: Window %d changed size to %dx%d",
                            event->window.windowID, event->window.data1,
                            event->window.data2);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    SDL_Log("SDL EVENT: Window %d minimized", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    SDL_Log("SDL EVENT: Window %d maximized", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_RESTORED:
                    SDL_Log("SDL EVENT: Window %d restored", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    SDL_Log("SDL EVENT: Mouse entered window %d",
                            event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    SDL_Log("SDL EVENT: Mouse left window %d", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    SDL_Log("SDL EVENT: Window %d gained keyboard focus",
                            event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    SDL_Log("SDL EVENT: Window %d lost keyboard focus",
                            event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    SDL_Log("SDL EVENT: Window %d closed", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_TAKE_FOCUS:
                    SDL_Log("SDL EVENT: Window %d take focus", event->window.windowID);
                    break;
                case SDL_WINDOWEVENT_HIT_TEST:
                    SDL_Log("SDL EVENT: Window %d hit test", event->window.windowID);
                    break;
                default:
                    SDL_Log("SDL EVENT: Window %d got unknown event %d",
                            event->window.windowID, event->window.event);
                    break;
            }
            break;
        case SDL_KEYDOWN:
            SDL_Log("SDL EVENT: Keyboard: key pressed  in window %d: scancode 0x%08X = %s, keycode 0x%08X = %s",
                    event->key.windowID,
                    event->key.keysym.scancode,
                    SDL_GetScancodeName(event->key.keysym.scancode),
                    event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
            break;
        case SDL_KEYUP:
            SDL_Log("SDL EVENT: Keyboard: key released in window %d: scancode 0x%08X = %s, keycode 0x%08X = %s",
                    event->key.windowID,
                    event->key.keysym.scancode,
                    SDL_GetScancodeName(event->key.keysym.scancode),
                    event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
            break;
        case SDL_TEXTINPUT:
            SDL_Log("SDL EVENT: Keyboard: text input \"%s\" in window %d",
                    event->text.text, event->text.windowID);
            break;
        case SDL_MOUSEMOTION:
            SDL_Log("SDL EVENT: Mouse: moved to %d,%d (%d,%d) in window %d",
                    event->motion.x, event->motion.y,
                    event->motion.xrel, event->motion.yrel,
                    event->motion.windowID);
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_Log("SDL EVENT: Mouse: button %d pressed at %d,%d with click count %d in window %d",
                    event->button.button, event->button.x, event->button.y, event->button.clicks,
                    event->button.windowID);
            break;
        case SDL_MOUSEBUTTONUP:
            SDL_Log("SDL EVENT: Mouse: button %d released at %d,%d with click count %d in window %d",
                    event->button.button, event->button.x, event->button.y, event->button.clicks,
                    event->button.windowID);
            break;
        case SDL_MOUSEWHEEL:
            SDL_Log("SDL EVENT: Mouse: wheel scrolled %d in x and %d in y (reversed: %d) in window %d",
                    event->wheel.x, event->wheel.y, event->wheel.direction, event->wheel.windowID);
            break;
        case SDL_JOYDEVICEADDED:
            SDL_Log("SDL EVENT: Joystick index %d attached",
                    event->jdevice.which);
            break;
        case SDL_JOYDEVICEREMOVED:
            SDL_Log("SDL EVENT: Joystick %d removed",
                    event->jdevice.which);
            break;
        case SDL_JOYBALLMOTION:
            SDL_Log("SDL EVENT: Joystick %d: ball %d moved by %d,%d",
                    event->jball.which, event->jball.ball, event->jball.xrel,
                    event->jball.yrel);
            break;
        case SDL_JOYHATMOTION:
        {
            const char *position = "UNKNOWN";
            switch (event->jhat.value) {
                case SDL_HAT_CENTERED:
                    position = "CENTER";
                    break;
                case SDL_HAT_UP:
                    position = "UP";
                    break;
                case SDL_HAT_RIGHTUP:
                    position = "RIGHTUP";
                    break;
                case SDL_HAT_RIGHT:
                    position = "RIGHT";
                    break;
                case SDL_HAT_RIGHTDOWN:
                    position = "RIGHTDOWN";
                    break;
                case SDL_HAT_DOWN:
                    position = "DOWN";
                    break;
                case SDL_HAT_LEFTDOWN:
                    position = "LEFTDOWN";
                    break;
                case SDL_HAT_LEFT:
                    position = "LEFT";
                    break;
                case SDL_HAT_LEFTUP:
                    position = "LEFTUP";
                    break;
            }
            SDL_Log("SDL EVENT: Joystick %d: hat %d moved to %s", event->jhat.which,
                    event->jhat.hat, position);
        }
            break;
        case SDL_JOYBUTTONDOWN:
            SDL_Log("SDL EVENT: Joystick %d: button %d pressed",
                    event->jbutton.which, event->jbutton.button);
            break;
        case SDL_JOYBUTTONUP:
            SDL_Log("SDL EVENT: Joystick %d: button %d released",
                    event->jbutton.which, event->jbutton.button);
            break;
        case SDL_CONTROLLERDEVICEADDED:
            SDL_Log("SDL EVENT: Controller index %d attached",
                    event->cdevice.which);
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            SDL_Log("SDL EVENT: Controller %d removed",
                    event->cdevice.which);
            break;
        case SDL_CONTROLLERAXISMOTION:
            SDL_Log("SDL EVENT: Controller %d axis %d ('%s') value: %d",
                    event->caxis.which,
                    event->caxis.axis,
                    ControllerAxisName((SDL_GameControllerAxis)event->caxis.axis),
                    event->caxis.value);
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            SDL_Log("SDL EVENT: Controller %d button %d ('%s') down",
                    event->cbutton.which, event->cbutton.button,
                    ControllerButtonName((SDL_GameControllerButton)event->cbutton.button));
            break;
        case SDL_CONTROLLERBUTTONUP:
            SDL_Log("SDL EVENT: Controller %d button %d ('%s') up",
                    event->cbutton.which, event->cbutton.button,
                    ControllerButtonName((SDL_GameControllerButton)event->cbutton.button));
            break;
        case SDL_CLIPBOARDUPDATE:
            SDL_Log("SDL EVENT: Clipboard updated");
            break;
            
        case SDL_FINGERDOWN:
        case SDL_FINGERUP:
            SDL_Log("SDL EVENT: Finger: %s touch=%ld, finger=%ld, x=%f, y=%f, dx=%f, dy=%f, pressure=%f",
                    (event->type == SDL_FINGERDOWN) ? "down" : "up",
                    (long) event->tfinger.touchId,
                    (long) event->tfinger.fingerId,
                    event->tfinger.x, event->tfinger.y,
                    event->tfinger.dx, event->tfinger.dy, event->tfinger.pressure);
            break;
        case SDL_DOLLARGESTURE:
            SDL_Log("SDL_EVENT: Dollar gesture detect: %" SDL_PRIs64, (Sint64) event->dgesture.gestureId);
            break;
        case SDL_DOLLARRECORD:
            SDL_Log("SDL_EVENT: Dollar gesture record: %" SDL_PRIs64, (Sint64) event->dgesture.gestureId);
            break;
        case SDL_MULTIGESTURE:
            SDL_Log("SDL_EVENT: Multi gesture fingers: %d", event->mgesture.numFingers);
            break;
            
        case SDL_RENDER_DEVICE_RESET:
            SDL_Log("SDL EVENT: render device reset");
            break;
        case SDL_RENDER_TARGETS_RESET:
            SDL_Log("SDL EVENT: render targets reset");
            break;
            
        case SDL_QUIT:
            SDL_Log("SDL EVENT: Quit requested");
            break;
        case SDL_USEREVENT:
            SDL_Log("SDL EVENT: User event %d", event->user.code);
            break;
        default:
            SDL_Log("Unknown event %04x", event->type);
            break;
    }
}

static void
FullscreenTo(int index, int windowId)
{
    Uint32 flags;
    struct SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Window *window = SDL_GetWindowFromID(windowId);
    if (!window) {
        return;
    }
    
    SDL_GetDisplayBounds( index, &rect );
    
    flags = SDL_GetWindowFlags(window);
    if (flags & SDL_WINDOW_FULLSCREEN) {
        SDL_SetWindowFullscreen( window, SDL_FALSE );
        SDL_Delay( 15 );
    }
    
    SDL_SetWindowPosition( window, rect.x, rect.y );
    SDL_SetWindowFullscreen( window, SDL_TRUE );
}

static void
SDLTest_CommonEvent(SDLTest_CommonState * state, SDL_Event * event, int *done)
{
    int i;
    static SDL_MouseMotionEvent lastEvent;
    
    if (state->verbose & VERBOSE_EVENT) {
        SDLTest_PrintEvent(event);
    }
    
    switch (event->type) {
        case SDL_APP_DIDENTERFOREGROUND:
            SDL_Log("SDL_APP_DIDENTERFOREGROUND");
            break;
            
        case SDL_APP_DIDENTERBACKGROUND:
            SDL_Log("SDL_APP_DIDENTERBACKGROUND");
            njli::NJLIGameEngine::didEnterBackground();
            break;
            
        case SDL_APP_LOWMEMORY:
            SDL_Log("SDL_APP_LOWMEMORY");
            njli::NJLIGameEngine::receivedMemoryWarning();
            break;
            
        case SDL_APP_TERMINATING:
            SDL_Log("SDL_APP_TERMINATING");
            njli::NJLIGameEngine::willTerminate();
            break;
            
        case SDL_APP_WILLENTERBACKGROUND:
            SDL_Log("SDL_APP_WILLENTERBACKGROUND");
            break;
            
        case SDL_APP_WILLENTERFOREGROUND:
            SDL_Log("SDL_APP_WILLENTERFOREGROUND");
            njli::NJLIGameEngine::willEnterForeground();
            break;
            
        case SDL_WINDOWEVENT:
            switch (event->window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                {
                    SDL_Log("Window %d resized to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
                    
                    njli::NJLIGameEngine::resize(0, 0, event->window.data1, event->window.data2, 0);
                    
                    break;
                }
                case SDL_WINDOWEVENT_CLOSE:
                {
                    SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
                    if (window) {
                        for (i = 0; i < state->num_windows; ++i) {
                            if (window == state->windows[i]) {
                                if (state->targets[i]) {
                                    SDL_DestroyTexture(state->targets[i]);
                                    state->targets[i] = NULL;
                                }
                                if (state->renderers[i]) {
                                    SDL_DestroyRenderer(state->renderers[i]);
                                    state->renderers[i] = NULL;
                                }
                                SDL_DestroyWindow(state->windows[i]);
                                state->windows[i] = NULL;
                                break;
                            }
                        }
                    }
                }
                    break;
            }
            break;
        case SDL_KEYDOWN: {
            bool withControl = !!(event->key.keysym.mod & KMOD_CTRL);
            bool withShift = !!(event->key.keysym.mod & KMOD_SHIFT);
            bool withAlt = !!(event->key.keysym.mod & KMOD_ALT);
            
            switch (event->key.keysym.sym) {
                    /* Add hotkeys here */
                case SDLK_PRINTSCREEN: {
                    SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                    if (window) {
                        for (i = 0; i < state->num_windows; ++i) {
                            if (window == state->windows[i]) {
                                SDLTest_ScreenShot(state->renderers[i]);
                            }
                        }
                    }
                }
                    break;
                case SDLK_EQUALS:
                    if (withControl) {
                        /* Ctrl-+ double the size of the window */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            int w, h;
                            SDL_GetWindowSize(window, &w, &h);
                            SDL_SetWindowSize(window, w*2, h*2);
                        }
                    }
                    break;
                case SDLK_MINUS:
                    if (withControl) {
                        /* Ctrl-- half the size of the window */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            int w, h;
                            SDL_GetWindowSize(window, &w, &h);
                            SDL_SetWindowSize(window, w/2, h/2);
                        }
                    }
                    break;
                case SDLK_o:
                    if (withControl) {
                        /* Ctrl-O (or Ctrl-Shift-O) changes window opacity. */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            float opacity;
                            if (SDL_GetWindowOpacity(window, &opacity) == 0) {
                                if (withShift) {
                                    opacity += 0.20f;
                                } else {
                                    opacity -= 0.20f;
                                }
                                SDL_SetWindowOpacity(window, opacity);
                            }
                        }
                    }
                    break;
                    
                case SDLK_c:
                    if (withControl) {
                        /* Ctrl-C copy awesome text! */
                        SDL_SetClipboardText("SDL rocks!\nYou know it!");
                        printf("Copied text to clipboard\n");
                    }
                    if (withAlt) {
                        /* Alt-C toggle a render clip rectangle */
                        for (i = 0; i < state->num_windows; ++i) {
                            int w, h;
                            if (state->renderers[i]) {
                                SDL_Rect clip;
                                SDL_GetWindowSize(state->windows[i], &w, &h);
                                SDL_RenderGetClipRect(state->renderers[i], &clip);
                                if (SDL_RectEmpty(&clip)) {
                                    clip.x = w/4;
                                    clip.y = h/4;
                                    clip.w = w/2;
                                    clip.h = h/2;
                                    SDL_RenderSetClipRect(state->renderers[i], &clip);
                                } else {
                                    SDL_RenderSetClipRect(state->renderers[i], NULL);
                                }
                            }
                        }
                    }
                    if (withShift) {
                        SDL_Window *current_win = SDL_GetKeyboardFocus();
                        if (current_win) {
                            const bool shouldCapture = (SDL_GetWindowFlags(current_win) & SDL_WINDOW_MOUSE_CAPTURE) == 0;
                            const int rc = SDL_CaptureMouse((SDL_bool)shouldCapture);
                            SDL_Log("%sapturing mouse %s!\n", shouldCapture ? "C" : "Unc", (rc == 0) ? "succeeded" : "failed");
                        }
                    }
                    break;
                case SDLK_v:
                    if (withControl) {
                        /* Ctrl-V paste awesome text! */
                        char *text = SDL_GetClipboardText();
                        if (*text) {
                            printf("Clipboard: %s\n", text);
                        } else {
                            printf("Clipboard is empty\n");
                        }
                        SDL_free(text);
                    }
                    break;
                case SDLK_g:
                    if (withControl) {
                        /* Ctrl-G toggle grab */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            SDL_SetWindowGrab(window, !SDL_GetWindowGrab(window) ? SDL_TRUE : SDL_FALSE);
                        }
                    }
                    break;
                case SDLK_m:
                    if (withControl) {
                        /* Ctrl-M maximize */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            Uint32 flags = SDL_GetWindowFlags(window);
                            if (flags & SDL_WINDOW_MAXIMIZED) {
                                SDL_RestoreWindow(window);
                            } else {
                                SDL_MaximizeWindow(window);
                            }
                        }
                    }
                    break;
                case SDLK_r:
                    if (withControl) {
                        /* Ctrl-R toggle mouse relative mode */
                        SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode() ? SDL_TRUE : SDL_FALSE);
                    }
                    break;
                case SDLK_z:
                    if (withControl) {
                        /* Ctrl-Z minimize */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            SDL_MinimizeWindow(window);
                        }
                    }
                    break;
                case SDLK_RETURN:
                    if (withControl) {
                        /* Ctrl-Enter toggle fullscreen */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            Uint32 flags = SDL_GetWindowFlags(window);
                            if (flags & SDL_WINDOW_FULLSCREEN) {
                                SDL_SetWindowFullscreen(window, SDL_FALSE);
                            } else {
                                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                            }
                        }
                    } else if (withAlt) {
                        /* Alt-Enter toggle fullscreen desktop */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            Uint32 flags = SDL_GetWindowFlags(window);
                            if (flags & SDL_WINDOW_FULLSCREEN) {
                                SDL_SetWindowFullscreen(window, SDL_FALSE);
                            } else {
                                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                            }
                        }
                    } else if (withShift) {
                        /* Shift-Enter toggle fullscreen desktop / fullscreen */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            Uint32 flags = SDL_GetWindowFlags(window);
                            if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) {
                                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                            } else {
                                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                            }
                        }
                    }
                    
                    break;
                case SDLK_b:
                    if (withControl) {
                        /* Ctrl-B toggle window border */
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        if (window) {
                            const Uint32 flags = SDL_GetWindowFlags(window);
                            const SDL_bool b = ((flags & SDL_WINDOW_BORDERLESS) != 0) ? SDL_TRUE : SDL_FALSE;
                            SDL_SetWindowBordered(window, b);
                        }
                    }
                    break;
                case SDLK_a:
                    if (withControl) {
                        /* Ctrl-A reports absolute mouse position. */
                        int x, y;
                        const Uint32 mask = SDL_GetGlobalMouseState(&x, &y);
                        SDL_Log("ABSOLUTE MOUSE: (%d, %d)%s%s%s%s%s\n", x, y,
                                (mask & SDL_BUTTON_LMASK) ? " [LBUTTON]" : "",
                                (mask & SDL_BUTTON_MMASK) ? " [MBUTTON]" : "",
                                (mask & SDL_BUTTON_RMASK) ? " [RBUTTON]" : "",
                                (mask & SDL_BUTTON_X1MASK) ? " [X2BUTTON]" : "",
                                (mask & SDL_BUTTON_X2MASK) ? " [X2BUTTON]" : "");
                    }
                    break;
                case SDLK_0:
                    if (withControl) {
                        SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Test Message", "You're awesome!", window);
                    }
                    break;
                case SDLK_1:
                    if (withControl) {
                        FullscreenTo(0, event->key.windowID);
                    }
                    break;
                case SDLK_2:
                    if (withControl) {
                        FullscreenTo(1, event->key.windowID);
                    }
                    break;
                case SDLK_ESCAPE:
                    *done = 1;
                    break;
                case SDLK_SPACE:
                {
                    char message[256];
                    SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                    
                    SDL_snprintf(message, sizeof(message), "(%i, %i), rel (%i, %i)\n", lastEvent.x, lastEvent.y, lastEvent.xrel, lastEvent.yrel);
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Last mouse position", message, window);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case SDL_QUIT:
            *done = 1;
            break;
        case SDL_MOUSEMOTION:
            lastEvent = event->motion;
            break;
    }
}






























//#define NUM_SPRITES    100
//#define MAX_SPEED     1

static SDLTest_CommonState *state;
//static int num_sprites;
//static SDL_Texture **sprites;
static SDL_bool cycle_color;
static SDL_bool cycle_alpha;
static int cycle_direction = 1;
static int current_alpha = 0;
static int current_color = 0;
//static SDL_Rect *positions;
//static SDL_Rect *velocities;
static int sprite_w, sprite_h;
static SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;

/* Number of iterations to move sprites - used for visual tests. */
/* -1: infinite random moves (default); >=0: enables N deterministic moves */
static int iterations = -1;

int done;

/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void
quit(int rc)
{
//    SDL_free(sprites);
//    SDL_free(positions);
//    SDL_free(velocities);
    SDLTest_CommonQuit(state);
    exit(rc);
}

//int
//LoadSprite(const char *file)
//{
//    int i;
//    SDL_Surface *temp;
//    
//    /* Load the sprite image */
//    temp = SDL_LoadBMP(file);
//    if (temp == NULL) {
//        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load %s: %s", file, SDL_GetError());
//        return (-1);
//    }
//    sprite_w = temp->w;
//    sprite_h = temp->h;
//    
//    /* Set transparent pixel as the pixel at (0,0) */
//    if (temp->format->palette) {
//        SDL_SetColorKey(temp, 1, *(Uint8 *) temp->pixels);
//    } else {
//        switch (temp->format->BitsPerPixel) {
//            case 15:
//                SDL_SetColorKey(temp, 1, (*(Uint16 *) temp->pixels) & 0x00007FFF);
//                break;
//            case 16:
//                SDL_SetColorKey(temp, 1, *(Uint16 *) temp->pixels);
//                break;
//            case 24:
//                SDL_SetColorKey(temp, 1, (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
//                break;
//            case 32:
//                SDL_SetColorKey(temp, 1, *(Uint32 *) temp->pixels);
//                break;
//        }
//    }
//    
//    /* Create textures from the image */
//    for (i = 0; i < state->num_windows; ++i) {
//        SDL_Renderer *renderer = state->renderers[i];
//        sprites[i] = SDL_CreateTextureFromSurface(renderer, temp);
//        if (!sprites[i]) {
//            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture: %s\n", SDL_GetError());
//            SDL_FreeSurface(temp);
//            return (-1);
//        }
//        SDL_SetTextureBlendMode(sprites[i], blendMode);
//    }
//    SDL_FreeSurface(temp);
//    
//    /* We're ready to roll. :) */
//    return (0);
//}

//void
//MoveSprites(SDL_Renderer * renderer, SDL_Texture * sprite)
//{
//    int i;
//    SDL_Rect viewport, temp;
//    SDL_Rect *position, *velocity;
//    
//    /* Query the sizes */
//    SDL_RenderGetViewport(renderer, &viewport);
//    
//    /* Cycle the color and alpha, if desired */
//    if (cycle_color) {
//        current_color += cycle_direction;
//        if (current_color < 0) {
//            current_color = 0;
//            cycle_direction = -cycle_direction;
//        }
//        if (current_color > 255) {
//            current_color = 255;
//            cycle_direction = -cycle_direction;
//        }
//        SDL_SetTextureColorMod(sprite, 255, (Uint8) current_color,
//                               (Uint8) current_color);
//    }
//    if (cycle_alpha) {
//        current_alpha += cycle_direction;
//        if (current_alpha < 0) {
//            current_alpha = 0;
//            cycle_direction = -cycle_direction;
//        }
//        if (current_alpha > 255) {
//            current_alpha = 255;
//            cycle_direction = -cycle_direction;
//        }
//        SDL_SetTextureAlphaMod(sprite, (Uint8) current_alpha);
//    }
//    
//    /* Draw a gray background */
//    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
//    SDL_RenderClear(renderer);
//    
//    /* Test points */
//    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
//    SDL_RenderDrawPoint(renderer, 0, 0);
//    SDL_RenderDrawPoint(renderer, viewport.w-1, 0);
//    SDL_RenderDrawPoint(renderer, 0, viewport.h-1);
//    SDL_RenderDrawPoint(renderer, viewport.w-1, viewport.h-1);
//    
//    /* Test horizontal and vertical lines */
//    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
//    SDL_RenderDrawLine(renderer, 1, 0, viewport.w-2, 0);
//    SDL_RenderDrawLine(renderer, 1, viewport.h-1, viewport.w-2, viewport.h-1);
//    SDL_RenderDrawLine(renderer, 0, 1, 0, viewport.h-2);
//    SDL_RenderDrawLine(renderer, viewport.w-1, 1, viewport.w-1, viewport.h-2);
//    
//    /* Test fill and copy */
//    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//    temp.x = 1;
//    temp.y = 1;
//    temp.w = sprite_w;
//    temp.h = sprite_h;
//    SDL_RenderFillRect(renderer, &temp);
//    SDL_RenderCopy(renderer, sprite, NULL, &temp);
//    temp.x = viewport.w-sprite_w-1;
//    temp.y = 1;
//    temp.w = sprite_w;
//    temp.h = sprite_h;
//    SDL_RenderFillRect(renderer, &temp);
//    SDL_RenderCopy(renderer, sprite, NULL, &temp);
//    temp.x = 1;
//    temp.y = viewport.h-sprite_h-1;
//    temp.w = sprite_w;
//    temp.h = sprite_h;
//    SDL_RenderFillRect(renderer, &temp);
//    SDL_RenderCopy(renderer, sprite, NULL, &temp);
//    temp.x = viewport.w-sprite_w-1;
//    temp.y = viewport.h-sprite_h-1;
//    temp.w = sprite_w;
//    temp.h = sprite_h;
//    SDL_RenderFillRect(renderer, &temp);
//    SDL_RenderCopy(renderer, sprite, NULL, &temp);
//    
//    /* Test diagonal lines */
//    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
//    SDL_RenderDrawLine(renderer, sprite_w, sprite_h,
//                       viewport.w-sprite_w-2, viewport.h-sprite_h-2);
//    SDL_RenderDrawLine(renderer, viewport.w-sprite_w-2, sprite_h,
//                       sprite_w, viewport.h-sprite_h-2);
//    
//    /* Conditionally move the sprites, bounce at the wall */
//    if (iterations == -1 || iterations > 0) {
//        for (i = 0; i < num_sprites; ++i) {
//            position = &positions[i];
//            velocity = &velocities[i];
//            position->x += velocity->x;
//            if ((position->x < 0) || (position->x >= (viewport.w - sprite_w))) {
//                velocity->x = -velocity->x;
//                position->x += velocity->x;
//            }
//            position->y += velocity->y;
//            if ((position->y < 0) || (position->y >= (viewport.h - sprite_h))) {
//                velocity->y = -velocity->y;
//                position->y += velocity->y;
//            }
//            
//        }
//        
//        /* Countdown sprite-move iterations and disable color changes at iteration end - used for visual tests. */
//        if (iterations > 0) {
//            iterations--;
//            if (iterations == 0) {
//                cycle_alpha = SDL_FALSE;
//                cycle_color = SDL_FALSE;
//            }
//        }
//    }
//    
//    /* Draw sprites */
//    for (i = 0; i < num_sprites; ++i) {
//        position = &positions[i];
//        
//        /* Blit the sprite onto the screen */
//        SDL_RenderCopy(renderer, sprite, NULL, position);
//    }
//    
//    /* Update the screen! */
//    SDL_RenderPresent(renderer);
//}

static int
randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

static void
render(SDL_Renderer *renderer)
{

    Uint8 r, g, b;

    /* Clear the screen */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /*  Come up with a random rectangle */
    SDL_Rect rect;
    rect.w = randomInt(64, 128);
    rect.h = randomInt(64, 128);
    rect.x = randomInt(0, DEFAULT_WINDOW_WIDTH);
    rect.y = randomInt(0, DEFAULT_WINDOW_HEIGHT);

    /* Come up with a random color */
    r = randomInt(50, 255);
    g = randomInt(50, 255);
    b = randomInt(50, 255);
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    /*  Fill the rectangle in the color */
    SDL_RenderFillRect(renderer, &rect);

    /* update screen */
    SDL_RenderPresent(renderer);
}

static void
loop()
{
    
    int i;
    SDL_Event event;
    
    SDL_PumpEvents();
    /* Check for events */
    while (SDL_PollEvent(&event)) {
        SDLTest_CommonEvent(state, &event, &done);
    }
    
    njli::NJLIGameEngine::update(1.0f/60.0f);
    
    for (i = 0; i < state->num_windows; ++i) {
        if (state->windows[i] == NULL)
            continue;
//        MoveSprites(state->renderers[i], sprites[i]);
//        render(state->renderers[i]);
        njli::NJLIGameEngine::render();
    }
#ifdef __EMSCRIPTEN__
    if (done) {
        emscripten_cancel_main_loop();
    }
#endif
}

static SDLTest_CommonState *
SDLTest_CommonCreateState(char **argv, Uint32 flags)
{
    SDLTest_CommonState *state = (SDLTest_CommonState *)SDL_calloc(1, sizeof(*state));
    if (!state) {
        SDL_OutOfMemory();
        return NULL;
    }
    
    /* Initialize some defaults */
    state->argv = argv;
    state->flags = flags;
    state->window_title = argv[0];
    state->window_flags = 0;
    state->window_x = SDL_WINDOWPOS_UNDEFINED;
    state->window_y = SDL_WINDOWPOS_UNDEFINED;
    state->window_w = DEFAULT_WINDOW_WIDTH;
    state->window_h = DEFAULT_WINDOW_HEIGHT;
    state->num_windows = 1;
    state->audiospec.freq = 22050;
    state->audiospec.format = AUDIO_S16;
    state->audiospec.channels = 2;
    state->audiospec.samples = 2048;
    
    /* Set some very sane GL defaults */
    state->gl_red_size = 3;
    state->gl_green_size = 3;
    state->gl_blue_size = 2;
    state->gl_alpha_size = 0;
    state->gl_buffer_size = 0;
    state->gl_depth_size = 16;
    state->gl_stencil_size = 0;
    state->gl_double_buffer = 1;
    state->gl_accum_red_size = 0;
    state->gl_accum_green_size = 0;
    state->gl_accum_blue_size = 0;
    state->gl_accum_alpha_size = 0;
    state->gl_stereo = 0;
    state->gl_multisamplebuffers = 0;
    state->gl_multisamplesamples = 0;
    state->gl_retained_backing = 1;
    state->gl_accelerated = -1;
    state->gl_debug = 0;
    
    return state;
}

static int
SDLTest_CommonArg(SDLTest_CommonState * state, int index)
{
    char **argv = state->argv;
    
    if (SDL_strcasecmp(argv[index], "--video") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->videodriver = argv[index];
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--renderer") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->renderdriver = argv[index];
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--gldebug") == 0) {
        state->gl_debug = 1;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--info") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        if (SDL_strcasecmp(argv[index], "all") == 0) {
            state->verbose |=
            (VERBOSE_VIDEO | VERBOSE_MODES | VERBOSE_RENDER |
             VERBOSE_EVENT);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "video") == 0) {
            state->verbose |= VERBOSE_VIDEO;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "modes") == 0) {
            state->verbose |= VERBOSE_MODES;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "render") == 0) {
            state->verbose |= VERBOSE_RENDER;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "event") == 0) {
            state->verbose |= VERBOSE_EVENT;
            return 2;
        }
        return -1;
    }
    if (SDL_strcasecmp(argv[index], "--log") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        if (SDL_strcasecmp(argv[index], "all") == 0) {
            SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "error") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "system") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_SYSTEM, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "audio") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_AUDIO, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "video") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "render") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "input") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_INPUT, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        return -1;
    }
    if (SDL_strcasecmp(argv[index], "--display") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->display = SDL_atoi(argv[index]);
        if (SDL_WINDOWPOS_ISUNDEFINED(state->window_x)) {
            state->window_x = SDL_WINDOWPOS_UNDEFINED_DISPLAY(state->display);
            state->window_y = SDL_WINDOWPOS_UNDEFINED_DISPLAY(state->display);
        }
        if (SDL_WINDOWPOS_ISCENTERED(state->window_x)) {
            state->window_x = SDL_WINDOWPOS_CENTERED_DISPLAY(state->display);
            state->window_y = SDL_WINDOWPOS_CENTERED_DISPLAY(state->display);
        }
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--fullscreen") == 0) {
        state->window_flags |= SDL_WINDOW_FULLSCREEN;
        state->num_windows = 1;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--fullscreen-desktop") == 0) {
        state->window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        state->num_windows = 1;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--allow-highdpi") == 0) {
        state->window_flags |= SDL_WINDOW_ALLOW_HIGHDPI;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--windows") == 0) {
        ++index;
        if (!argv[index] || !SDL_isdigit(*argv[index])) {
            return -1;
        }
        if (!(state->window_flags & SDL_WINDOW_FULLSCREEN)) {
            state->num_windows = SDL_atoi(argv[index]);
        }
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--title") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->window_title = argv[index];
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--icon") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->window_icon = argv[index];
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--center") == 0) {
        state->window_x = SDL_WINDOWPOS_CENTERED;
        state->window_y = SDL_WINDOWPOS_CENTERED;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--position") == 0) {
        char *x, *y;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        x = argv[index];
        y = argv[index];
        while (*y && *y != ',') {
            ++y;
        }
        if (!*y) {
            return -1;
        }
        *y++ = '\0';
        state->window_x = SDL_atoi(x);
        state->window_y = SDL_atoi(y);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--geometry") == 0) {
        char *w, *h;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        w = argv[index];
        h = argv[index];
        while (*h && *h != 'x') {
            ++h;
        }
        if (!*h) {
            return -1;
        }
        *h++ = '\0';
        state->window_w = SDL_atoi(w);
        state->window_h = SDL_atoi(h);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--min-geometry") == 0) {
        char *w, *h;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        w = argv[index];
        h = argv[index];
        while (*h && *h != 'x') {
            ++h;
        }
        if (!*h) {
            return -1;
        }
        *h++ = '\0';
        state->window_minW = SDL_atoi(w);
        state->window_minH = SDL_atoi(h);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--max-geometry") == 0) {
        char *w, *h;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        w = argv[index];
        h = argv[index];
        while (*h && *h != 'x') {
            ++h;
        }
        if (!*h) {
            return -1;
        }
        *h++ = '\0';
        state->window_maxW = SDL_atoi(w);
        state->window_maxH = SDL_atoi(h);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--logical") == 0) {
        char *w, *h;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        w = argv[index];
        h = argv[index];
        while (*h && *h != 'x') {
            ++h;
        }
        if (!*h) {
            return -1;
        }
        *h++ = '\0';
        state->logical_w = SDL_atoi(w);
        state->logical_h = SDL_atoi(h);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--scale") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->scale = (float)SDL_atof(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--depth") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->depth = SDL_atoi(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--refresh") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->refresh_rate = SDL_atoi(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--vsync") == 0) {
        state->render_flags |= SDL_RENDERER_PRESENTVSYNC;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--noframe") == 0) {
        state->window_flags |= SDL_WINDOW_BORDERLESS;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--resize") == 0) {
        state->window_flags |= SDL_WINDOW_RESIZABLE;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--minimize") == 0) {
        state->window_flags |= SDL_WINDOW_MINIMIZED;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--maximize") == 0) {
        state->window_flags |= SDL_WINDOW_MAXIMIZED;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--grab") == 0) {
        state->window_flags |= SDL_WINDOW_INPUT_GRABBED;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--rate") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->audiospec.freq = SDL_atoi(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--format") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        if (SDL_strcasecmp(argv[index], "U8") == 0) {
            state->audiospec.format = AUDIO_U8;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "S8") == 0) {
            state->audiospec.format = AUDIO_S8;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "U16") == 0) {
            state->audiospec.format = AUDIO_U16;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "U16LE") == 0) {
            state->audiospec.format = AUDIO_U16LSB;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "U16BE") == 0) {
            state->audiospec.format = AUDIO_U16MSB;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "S16") == 0) {
            state->audiospec.format = AUDIO_S16;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "S16LE") == 0) {
            state->audiospec.format = AUDIO_S16LSB;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "S16BE") == 0) {
            state->audiospec.format = AUDIO_S16MSB;
            return 2;
        }
        return -1;
    }
    if (SDL_strcasecmp(argv[index], "--channels") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->audiospec.channels = (Uint8) SDL_atoi(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--samples") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->audiospec.samples = (Uint16) SDL_atoi(argv[index]);
        return 2;
    }
    if ((SDL_strcasecmp(argv[index], "-h") == 0)
        || (SDL_strcasecmp(argv[index], "--help") == 0)) {
        /* Print the usage message */
        return -1;
    }
    if (SDL_strcmp(argv[index], "-NSDocumentRevisionsDebugMode") == 0) {
        /* Debug flag sent by Xcode */
        return 2;
    }
    return 0;
}

static const char *
SDLTest_CommonUsage(SDLTest_CommonState * state)
{
    switch (state->flags & (SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        case SDL_INIT_VIDEO:
            return VIDEO_USAGE;
        case SDL_INIT_AUDIO:
            return AUDIO_USAGE;
        case (SDL_INIT_VIDEO | SDL_INIT_AUDIO):
            return VIDEO_USAGE " " AUDIO_USAGE;
        default:
            return "";
    }
}

static void
SDLTest_PrintRendererFlag(Uint32 flag)
{
    switch (flag) {
        case SDL_RENDERER_PRESENTVSYNC:
            fprintf(stderr, "PresentVSync");
            break;
        case SDL_RENDERER_ACCELERATED:
            fprintf(stderr, "Accelerated");
            break;
        default:
            fprintf(stderr, "0x%8.8x", flag);
            break;
    }
}

static void
SDLTest_PrintPixelFormat(Uint32 format)
{
    switch (format) {
        case SDL_PIXELFORMAT_UNKNOWN:
            fprintf(stderr, "Unknwon");
            break;
        case SDL_PIXELFORMAT_INDEX1LSB:
            fprintf(stderr, "Index1LSB");
            break;
        case SDL_PIXELFORMAT_INDEX1MSB:
            fprintf(stderr, "Index1MSB");
            break;
        case SDL_PIXELFORMAT_INDEX4LSB:
            fprintf(stderr, "Index4LSB");
            break;
        case SDL_PIXELFORMAT_INDEX4MSB:
            fprintf(stderr, "Index4MSB");
            break;
        case SDL_PIXELFORMAT_INDEX8:
            fprintf(stderr, "Index8");
            break;
        case SDL_PIXELFORMAT_RGB332:
            fprintf(stderr, "RGB332");
            break;
        case SDL_PIXELFORMAT_RGB444:
            fprintf(stderr, "RGB444");
            break;
        case SDL_PIXELFORMAT_RGB555:
            fprintf(stderr, "RGB555");
            break;
        case SDL_PIXELFORMAT_BGR555:
            fprintf(stderr, "BGR555");
            break;
        case SDL_PIXELFORMAT_ARGB4444:
            fprintf(stderr, "ARGB4444");
            break;
        case SDL_PIXELFORMAT_ABGR4444:
            fprintf(stderr, "ABGR4444");
            break;
        case SDL_PIXELFORMAT_ARGB1555:
            fprintf(stderr, "ARGB1555");
            break;
        case SDL_PIXELFORMAT_ABGR1555:
            fprintf(stderr, "ABGR1555");
            break;
        case SDL_PIXELFORMAT_RGB565:
            fprintf(stderr, "RGB565");
            break;
        case SDL_PIXELFORMAT_BGR565:
            fprintf(stderr, "BGR565");
            break;
        case SDL_PIXELFORMAT_RGB24:
            fprintf(stderr, "RGB24");
            break;
        case SDL_PIXELFORMAT_BGR24:
            fprintf(stderr, "BGR24");
            break;
        case SDL_PIXELFORMAT_RGB888:
            fprintf(stderr, "RGB888");
            break;
        case SDL_PIXELFORMAT_BGR888:
            fprintf(stderr, "BGR888");
            break;
        case SDL_PIXELFORMAT_ARGB8888:
            fprintf(stderr, "ARGB8888");
            break;
        case SDL_PIXELFORMAT_RGBA8888:
            fprintf(stderr, "RGBA8888");
            break;
        case SDL_PIXELFORMAT_ABGR8888:
            fprintf(stderr, "ABGR8888");
            break;
        case SDL_PIXELFORMAT_BGRA8888:
            fprintf(stderr, "BGRA8888");
            break;
        case SDL_PIXELFORMAT_ARGB2101010:
            fprintf(stderr, "ARGB2101010");
            break;
        case SDL_PIXELFORMAT_YV12:
            fprintf(stderr, "YV12");
            break;
        case SDL_PIXELFORMAT_IYUV:
            fprintf(stderr, "IYUV");
            break;
        case SDL_PIXELFORMAT_YUY2:
            fprintf(stderr, "YUY2");
            break;
        case SDL_PIXELFORMAT_UYVY:
            fprintf(stderr, "UYVY");
            break;
        case SDL_PIXELFORMAT_YVYU:
            fprintf(stderr, "YVYU");
            break;
        case SDL_PIXELFORMAT_NV12:
            fprintf(stderr, "NV12");
            break;
        case SDL_PIXELFORMAT_NV21:
            fprintf(stderr, "NV21");
            break;
        default:
            fprintf(stderr, "0x%8.8x", format);
            break;
    }
}

static void
SDLTest_PrintRenderer(SDL_RendererInfo * info)
{
    int i, count;
    
    fprintf(stderr, "  Renderer %s:\n", info->name);
    
    fprintf(stderr, "    Flags: 0x%8.8X", info->flags);
    fprintf(stderr, " (");
    count = 0;
    for (i = 0; i < sizeof(info->flags) * 8; ++i) {
        Uint32 flag = (1 << i);
        if (info->flags & flag) {
            if (count > 0) {
                fprintf(stderr, " | ");
            }
            SDLTest_PrintRendererFlag(flag);
            ++count;
        }
    }
    fprintf(stderr, ")\n");
    
    fprintf(stderr, "    Texture formats (%d): ", info->num_texture_formats);
    for (i = 0; i < (int) info->num_texture_formats; ++i) {
        if (i > 0) {
            fprintf(stderr, ", ");
        }
        SDLTest_PrintPixelFormat(info->texture_formats[i]);
    }
    fprintf(stderr, "\n");
    
    if (info->max_texture_width || info->max_texture_height) {
        fprintf(stderr, "    Max Texture Size: %dx%d\n",
                info->max_texture_width, info->max_texture_height);
    }
}

static SDL_Surface *
SDLTest_LoadIcon(const char *file)
{
    SDL_Surface *icon;
    
    /* Load the icon surface */
    icon = SDL_LoadBMP(file);
    if (icon == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return (NULL);
    }
    
    if (icon->format->palette) {
        /* Set the colorkey */
        SDL_SetColorKey(icon, 1, *((Uint8 *) icon->pixels));
    }
    
    return (icon);
}


static SDL_bool
SDLTest_CommonInit(SDLTest_CommonState * state)
{
    int i, j, m, n, w, h;
    SDL_DisplayMode fullscreen_mode;
    
    if (state->flags & SDL_INIT_VIDEO) {
        if (state->verbose & VERBOSE_VIDEO) {
            n = SDL_GetNumVideoDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in video drivers\n");
            } else {
                fprintf(stderr, "Built-in video drivers:");
                for (i = 0; i < n; ++i) {
                    if (i > 0) {
                        fprintf(stderr, ",");
                    }
                    fprintf(stderr, " %s", SDL_GetVideoDriver(i));
                }
                fprintf(stderr, "\n");
            }
        }
        if (SDL_VideoInit(state->videodriver) < 0) {
            fprintf(stderr, "Couldn't initialize video driver: %s\n",
                    SDL_GetError());
            return SDL_FALSE;
        }
        if (state->verbose & VERBOSE_VIDEO) {
            fprintf(stderr, "Video driver: %s\n",
                    SDL_GetCurrentVideoDriver());
        }
        
        /* Upload GL settings */
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, state->gl_red_size);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, state->gl_green_size);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, state->gl_blue_size);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, state->gl_alpha_size);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, state->gl_double_buffer);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, state->gl_buffer_size);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, state->gl_depth_size);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, state->gl_stencil_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, state->gl_accum_red_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, state->gl_accum_green_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, state->gl_accum_blue_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, state->gl_accum_alpha_size);
        SDL_GL_SetAttribute(SDL_GL_STEREO, state->gl_stereo);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, state->gl_multisamplebuffers);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, state->gl_multisamplesamples);
        if (state->gl_accelerated >= 0) {
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,
                                state->gl_accelerated);
        }
        SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, state->gl_retained_backing);
        if (state->gl_major_version) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, state->gl_major_version);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, state->gl_minor_version);
        }
        if (state->gl_debug) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        }
        if (state->gl_profile_mask) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, state->gl_profile_mask);
        }
        
        if (state->verbose & VERBOSE_MODES) {
            SDL_Rect bounds;
            SDL_DisplayMode mode;
            int bpp;
            Uint32 Rmask, Gmask, Bmask, Amask;
#if SDL_VIDEO_DRIVER_WINDOWS
            int adapterIndex = 0;
            int outputIndex = 0;
#endif
            n = SDL_GetNumVideoDisplays();
            fprintf(stderr, "Number of displays: %d\n", n);
            for (i = 0; i < n; ++i) {
                fprintf(stderr, "Display %d: %s\n", i, SDL_GetDisplayName(i));
                
                SDL_zero(bounds);
                SDL_GetDisplayBounds(i, &bounds);
                fprintf(stderr, "Bounds: %dx%d at %d,%d\n", bounds.w, bounds.h, bounds.x, bounds.y);
                
                SDL_GetDesktopDisplayMode(i, &mode);
                SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask, &Gmask,
                                           &Bmask, &Amask);
                fprintf(stderr,
                        "  Current mode: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                        mode.w, mode.h, mode.refresh_rate, bpp,
                        SDL_GetPixelFormatName(mode.format));
                if (Rmask || Gmask || Bmask) {
                    fprintf(stderr, "      Red Mask   = 0x%.8x\n", Rmask);
                    fprintf(stderr, "      Green Mask = 0x%.8x\n", Gmask);
                    fprintf(stderr, "      Blue Mask  = 0x%.8x\n", Bmask);
                    if (Amask)
                        fprintf(stderr, "      Alpha Mask = 0x%.8x\n", Amask);
                }
                
                /* Print available fullscreen video modes */
                m = SDL_GetNumDisplayModes(i);
                if (m == 0) {
                    fprintf(stderr, "No available fullscreen video modes\n");
                } else {
                    fprintf(stderr, "  Fullscreen video modes:\n");
                    for (j = 0; j < m; ++j) {
                        SDL_GetDisplayMode(i, j, &mode);
                        SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask,
                                                   &Gmask, &Bmask, &Amask);
                        fprintf(stderr,
                                "    Mode %d: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                                j, mode.w, mode.h, mode.refresh_rate, bpp,
                                SDL_GetPixelFormatName(mode.format));
                        if (Rmask || Gmask || Bmask) {
                            fprintf(stderr, "        Red Mask   = 0x%.8x\n",
                                    Rmask);
                            fprintf(stderr, "        Green Mask = 0x%.8x\n",
                                    Gmask);
                            fprintf(stderr, "        Blue Mask  = 0x%.8x\n",
                                    Bmask);
                            if (Amask)
                                fprintf(stderr,
                                        "        Alpha Mask = 0x%.8x\n",
                                        Amask);
                        }
                    }
                }
                
#if SDL_VIDEO_DRIVER_WINDOWS
                /* Print the D3D9 adapter index */
                adapterIndex = SDL_Direct3D9GetAdapterIndex( i );
                fprintf( stderr, "D3D9 Adapter Index: %d", adapterIndex );
                
                /* Print the DXGI adapter and output indices */
                SDL_DXGIGetOutputInfo(i, &adapterIndex, &outputIndex);
                fprintf( stderr, "DXGI Adapter Index: %d  Output Index: %d", adapterIndex, outputIndex );
#endif
            }
        }
        
        if (state->verbose & VERBOSE_RENDER) {
            SDL_RendererInfo info;
            
            n = SDL_GetNumRenderDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in render drivers\n");
            } else {
                fprintf(stderr, "Built-in render drivers:\n");
                for (i = 0; i < n; ++i) {
                    SDL_GetRenderDriverInfo(i, &info);
                    SDLTest_PrintRenderer(&info);
                }
            }
        }
        
        SDL_zero(fullscreen_mode);
        switch (state->depth) {
            case 8:
                fullscreen_mode.format = SDL_PIXELFORMAT_INDEX8;
                break;
            case 15:
                fullscreen_mode.format = SDL_PIXELFORMAT_RGB555;
                break;
            case 16:
                fullscreen_mode.format = SDL_PIXELFORMAT_RGB565;
                break;
            case 24:
                fullscreen_mode.format = SDL_PIXELFORMAT_RGB24;
                break;
            default:
                fullscreen_mode.format = SDL_PIXELFORMAT_RGB888;
                break;
        }
        fullscreen_mode.refresh_rate = state->refresh_rate;
        
        state->windows =
        (SDL_Window **) SDL_malloc(state->num_windows *
                                   sizeof(*state->windows));
        state->renderers =
        (SDL_Renderer **) SDL_malloc(state->num_windows *
                                     sizeof(*state->renderers));
        state->targets =
        (SDL_Texture **) SDL_malloc(state->num_windows *
                                    sizeof(*state->targets));
        if (!state->windows || !state->renderers) {
            fprintf(stderr, "Out of memory!\n");
            return SDL_FALSE;
        }
        for (i = 0; i < state->num_windows; ++i) {
            char title[1024];
            
            if (state->num_windows > 1) {
                SDL_snprintf(title, SDL_arraysize(title), "%s %d",
                             state->window_title, i + 1);
            } else {
                SDL_strlcpy(title, state->window_title, SDL_arraysize(title));
            }
            state->windows[i] =
            SDL_CreateWindow(title, state->window_x, state->window_y,
                             state->window_w, state->window_h,
                             state->window_flags);
            if (!state->windows[i]) {
                fprintf(stderr, "Couldn't create window: %s\n",
                        SDL_GetError());
                return SDL_FALSE;
            }
            if (state->window_minW || state->window_minH) {
                SDL_SetWindowMinimumSize(state->windows[i], state->window_minW, state->window_minH);
            }
            if (state->window_maxW || state->window_maxH) {
                SDL_SetWindowMaximumSize(state->windows[i], state->window_maxW, state->window_maxH);
            }
            SDL_GetWindowSize(state->windows[i], &w, &h);
            if (!(state->window_flags & SDL_WINDOW_RESIZABLE) &&
                (w != state->window_w || h != state->window_h)) {
                printf("Window requested size %dx%d, got %dx%d\n", state->window_w, state->window_h, w, h);
                state->window_w = w;
                state->window_h = h;
            }
            if (SDL_SetWindowDisplayMode(state->windows[i], &fullscreen_mode) < 0) {
                fprintf(stderr, "Can't set up fullscreen display mode: %s\n",
                        SDL_GetError());
                return SDL_FALSE;
            }
            
            if (state->window_icon) {
                SDL_Surface *icon = SDLTest_LoadIcon(state->window_icon);
                if (icon) {
                    SDL_SetWindowIcon(state->windows[i], icon);
                    SDL_FreeSurface(icon);
                }
            }
            
            SDL_ShowWindow(state->windows[i]);
            
            state->renderers[i] = NULL;
            state->targets[i] = NULL;
            
            if (!state->skip_renderer
                && (state->renderdriver
                    || !(state->window_flags & SDL_WINDOW_OPENGL))) {
                    m = -1;
                    if (state->renderdriver) {
                        SDL_RendererInfo info;
                        n = SDL_GetNumRenderDrivers();
                        for (j = 0; j < n; ++j) {
                            SDL_GetRenderDriverInfo(j, &info);
                            if (SDL_strcasecmp(info.name, state->renderdriver) ==
                                0) {
                                m = j;
                                break;
                            }
                        }
                        if (m == -1) {
                            fprintf(stderr,
                                    "Couldn't find render driver named %s",
                                    state->renderdriver);
                            return SDL_FALSE;
                        }
                    }
                    state->renderers[i] = SDL_CreateRenderer(state->windows[i],
                                                             m, state->render_flags);
                    if (!state->renderers[i]) {
                        fprintf(stderr, "Couldn't create renderer: %s\n",
                                SDL_GetError());
                        return SDL_FALSE;
                    }
                    if (state->logical_w && state->logical_h) {
                        SDL_RenderSetLogicalSize(state->renderers[i], state->logical_w, state->logical_h);
                    } else if (state->scale) {
                        SDL_RenderSetScale(state->renderers[i], state->scale, state->scale);
                    }
                    if (state->verbose & VERBOSE_RENDER) {
                        SDL_RendererInfo info;
                        
                        fprintf(stderr, "Current renderer:\n");
                        SDL_GetRendererInfo(state->renderers[i], &info);
                        SDLTest_PrintRenderer(&info);
                    }
                }
        }
    }
    
    if (state->flags & SDL_INIT_AUDIO) {
        if (state->verbose & VERBOSE_AUDIO) {
            n = SDL_GetNumAudioDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in audio drivers\n");
            } else {
                fprintf(stderr, "Built-in audio drivers:");
                for (i = 0; i < n; ++i) {
                    if (i > 0) {
                        fprintf(stderr, ",");
                    }
                    fprintf(stderr, " %s", SDL_GetAudioDriver(i));
                }
                fprintf(stderr, "\n");
            }
        }
        if (SDL_AudioInit(state->audiodriver) < 0) {
            fprintf(stderr, "Couldn't initialize audio driver: %s\n",
                    SDL_GetError());
            return SDL_FALSE;
        }
        if (state->verbose & VERBOSE_VIDEO) {
            fprintf(stderr, "Audio driver: %s\n",
                    SDL_GetCurrentAudioDriver());
        }
        
        if (SDL_OpenAudio(&state->audiospec, NULL) < 0) {
            fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
            return SDL_FALSE;
        }
    }
    
    return SDL_TRUE;
}


typedef struct {
    unsigned int a;
    unsigned int x;
    unsigned int c;
    unsigned int ah;
    unsigned int al;
} SDLTest_RandomContext;

/**
 * Context for shared random number generator
 */
static SDLTest_RandomContext rndContext;

/**
 * Counter for fuzzer invocations
 */
static int fuzzerInvocationCounter = 0;


static void SDLTest_RandomInit(SDLTest_RandomContext * rndContext, unsigned int xi, unsigned int ci)
{
    if (rndContext==NULL) return;
    
    /*
     * Choose a value for 'a' from this list
     * 1791398085 1929682203 1683268614 1965537969 1675393560
     * 1967773755 1517746329 1447497129 1655692410 1606218150
     * 2051013963 1075433238 1557985959 1781943330 1893513180
     * 1631296680 2131995753 2083801278 1873196400 1554115554
     */
    rndContext->a = 1655692410;
    rndContext->x = 30903;
    rndContext->c = 0;
    if (xi != 0) {
        rndContext->x = xi;
    }
    rndContext->c = ci;
    rndContext->ah = rndContext->a >> 16;
    rndContext->al = rndContext->a & 65535;
}

static void
SDLTest_FuzzerInit(Uint64 execKey)
{
    Uint32 a = (execKey >> 32) & 0x00000000FFFFFFFF;
    Uint32 b = execKey & 0x00000000FFFFFFFF;
    SDL_memset((void *)&rndContext, 0, sizeof(SDLTest_RandomContext));
    SDLTest_RandomInit(&rndContext, a, b);
    fuzzerInvocationCounter = 0;
}

int
main(int argc, char *argv[])
{
    int i;
    Uint32 then, now, frames;
    Uint64 seed;
    const char *icon = "icon.bmp";
    
    /* Initialize parameters */
//    num_sprites = NUM_SPRITES;
    
    /* Initialize test framework */
    state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);
    if (!state) {
        return 1;
    }
    
    
    for (i = 1; i < argc;) {
        int consumed;
        
        consumed = SDLTest_CommonArg(state, i);
        if (consumed == 0) {
            consumed = -1;
            if (SDL_strcasecmp(argv[i], "--blend") == 0) {
                if (argv[i + 1]) {
                    if (SDL_strcasecmp(argv[i + 1], "none") == 0) {
                        blendMode = SDL_BLENDMODE_NONE;
                        consumed = 2;
                    } else if (SDL_strcasecmp(argv[i + 1], "blend") == 0) {
                        blendMode = SDL_BLENDMODE_BLEND;
                        consumed = 2;
                    } else if (SDL_strcasecmp(argv[i + 1], "add") == 0) {
                        blendMode = SDL_BLENDMODE_ADD;
                        consumed = 2;
                    } else if (SDL_strcasecmp(argv[i + 1], "mod") == 0) {
                        blendMode = SDL_BLENDMODE_MOD;
                        consumed = 2;
                    }
                }
            } else if (SDL_strcasecmp(argv[i], "--iterations") == 0) {
                if (argv[i + 1]) {
                    iterations = SDL_atoi(argv[i + 1]);
                    if (iterations < -1) iterations = -1;
                    consumed = 2;
                }
            } else if (SDL_strcasecmp(argv[i], "--cyclecolor") == 0) {
                cycle_color = SDL_TRUE;
                consumed = 1;
            } else if (SDL_strcasecmp(argv[i], "--cyclealpha") == 0) {
                cycle_alpha = SDL_TRUE;
                consumed = 1;
            } else if (SDL_isdigit(*argv[i])) {
//                num_sprites = SDL_atoi(argv[i]);
                consumed = 1;
            } else if (argv[i][0] != '-') {
                icon = argv[i];
                consumed = 1;
            }
        }
        if (consumed < 0) {
            SDL_Log("Usage: %s %s [--blend none|blend|add|mod] [--cyclecolor] [--cyclealpha] [--iterations N] [num_sprites] [icon.bmp]\n",
                    argv[0], SDLTest_CommonUsage(state));
            quit(1);
        }
        i += consumed;
    }
    if (!SDLTest_CommonInit(state)) {
        quit(2);
    }
    
    /* Create the windows, initialize the renderers, and load the textures */
//    sprites =
//    (SDL_Texture **) SDL_malloc(state->num_windows * sizeof(*sprites));
//    if (!sprites) {
//        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Out of memory!\n");
//        quit(2);
//    }
    for (i = 0; i < state->num_windows; ++i) {
        SDL_Renderer *renderer = state->renderers[i];
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer);
    }
//    if (LoadSprite(icon) < 0) {
//        quit(2);
//    }
    
    /* Allocate memory for the sprite info */
//    positions = (SDL_Rect *) SDL_malloc(num_sprites * sizeof(SDL_Rect));
//    velocities = (SDL_Rect *) SDL_malloc(num_sprites * sizeof(SDL_Rect));
//    if (!positions || !velocities) {
//        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Out of memory!\n");
//        quit(2);
//    }
    
    /* Position sprites and set their velocities using the fuzzer */
    if (iterations >= 0) {
        /* Deterministic seed - used for visual tests */
        seed = (Uint64)iterations;
    } else {
        /* Pseudo-random seed generated from the time */
        seed = (Uint64)time(NULL);
    }
    SDLTest_FuzzerInit(seed);
//    for (i = 0; i < num_sprites; ++i) {
//        positions[i].x = SDLTest_RandomIntegerInRange(0, state->window_w - sprite_w);
//        positions[i].y = SDLTest_RandomIntegerInRange(0, state->window_h - sprite_h);
//        positions[i].w = sprite_w;
//        positions[i].h = sprite_h;
//        velocities[i].x = 0;
//        velocities[i].y = 0;
//        while (!velocities[i].x && !velocities[i].y) {
//            velocities[i].x = SDLTest_RandomIntegerInRange(-MAX_SPEED, MAX_SPEED);
//            velocities[i].y = SDLTest_RandomIntegerInRange(-MAX_SPEED, MAX_SPEED);
//        }
//    }
    
    /* Main render loop */
    frames = 0;
    then = SDL_GetTicks();
    done = 0;
    
    njli::NJLIGameEngine::create(SDL_GetPlatform());
    njli::NJLIGameEngine::resize(0,
                                 0,
                                 DEFAULT_WINDOW_WIDTH,
                                 DEFAULT_WINDOW_HEIGHT,
                                 0);
    
    done = (njli::NJLIGameEngine::start() == false);
    
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (!done) {
        ++frames;
        loop();
    }
#endif
    
    quit(0);
    
    return 0;
}

//#include "SDL.h"
//#include "Game.h"
//#include <time.h>
//
//#define SCREEN_WIDTH 320
//#define SCREEN_HEIGHT 480
//
//int
//randomInt(int min, int max)
//{
//    return min + rand() % (max - min + 1);
//}
//
//void
//render(SDL_Renderer *renderer)
//{
//
//    Uint8 r, g, b;
//
//    /* Clear the screen */
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_RenderClear(renderer);
//
//    /*  Come up with a random rectangle */
//    SDL_Rect rect;
//    rect.w = randomInt(64, 128);
//    rect.h = randomInt(64, 128);
//    rect.x = randomInt(0, SCREEN_WIDTH);
//    rect.y = randomInt(0, SCREEN_HEIGHT);
//
//    /* Come up with a random color */
//    r = randomInt(50, 255);
//    g = randomInt(50, 255);
//    b = randomInt(50, 255);
//    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
//
//    /*  Fill the rectangle in the color */
//    SDL_RenderFillRect(renderer, &rect);
//
//    /* update screen */
//    SDL_RenderPresent(renderer);
//}
//
//int
//main(int argc, char *argv[])
//{
//
//    SDL_Window *window;
//    SDL_Renderer *renderer;
//    int done;
//    SDL_Event event;
//
//    /* initialize SDL */
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        printf("Could not initialize SDL\n");
//        return 1;
//    }
//
//    /* seed random number generator */
//    srand(time(NULL));
//
//    /* create window and renderer */
//    window =
//        SDL_CreateWindow(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
//                         SDL_WINDOW_OPENGL);
//    if (!window) {
//        printf("Could not initialize Window\n");
//        return 1;
//    }
//    else
//    {
//        njli::NJLIGameEngine::create("deviceName");
//    }
//
//    renderer = SDL_CreateRenderer(window, -1, 0);
//    if (!renderer) {
//        printf("Could not create renderer\n");
//        return 1;
//    }
//
//    /* Enter render loop, waiting for user to quit */
//    done = 0;
//    while (!done) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                done = 1;
//            }
//        }
//        render(renderer);
//        SDL_Delay(1);
//    }
//
//    /* shutdown SDL */
//    SDL_Quit();
//
//    return 0;
//}
