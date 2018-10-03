#include <cstdio>
#include <cstdlib>
#include <cstring>
// Xlib & Xcb
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <xcb/xcb.h>
// openGL
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#define debug_boom(...) { fprintf(stderr,"[Error]\t\t"), fprintf(stderr,__VA_ARGS__), fprintf(stderr,"\n"); return -1; }
#define debug_log(...) fprintf(stderr,"[Log]\t\t"), fprintf(stderr,__VA_ARGS__), fprintf(stderr,"\n")

#ifdef DEBUG
#define subtask_(...) fprintf(stderr,"\033[01;35m[SubTask]-->\t"), fprintf(stderr,__VA_ARGS__), fprintf(stderr,"\033[00m\n");
#else
#define subtask_(...) ;
#endif

using namespace std;

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*,GLXFBConfig,GLXContext,Bool,const int*);

static bool isExtensionSupported(const char *list,const char *extname)
{
// Adapted from: https://zhuanlan.zhihu.com/p/28756646
	const char *h,*p,*t;
	p = strchr(extname,' ');
	if(p||*extname=='\0') return 0;
	for(h=list;;h=t)
	{
		p = strstr(h,extname);
		if(!p) return 0;
		t = p+strlen(extname);
		if((p==h||*(p-1)==' ')&&(*t==' '||*t=='\0'))
			return 1;
	}
}

static bool ctxErrorOccurred = 0;
static int ctxErrorHandler(Display *d,XErrorEvent *e)
{
	ctxErrorOccurred = 1;
	return 0;
}

void drawSth()
{
// Adapted from: https://zhuanlan.zhihu.com/p/28756646
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(-1., 1., -1., 1., 1., 20.); 

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.); 

	glBegin(GL_QUADS); 
	glColor3f(1., 0., 0.); 
	glVertex3f(-.75, -.75, 0.); 
	glColor3f(0., 1., 0.); 
	glVertex3f( .75, -.75, 0.); 
	glColor3f(0., 0., 1.); 
	glVertex3f( .75, .75, 0.); 
	glColor3f(1., 1., 0.); 
	glVertex3f(-.75, .75, 0.); 
	glEnd(); 
}

int main()
{
	xcb_connection_t 	*pConn;
	xcb_screen_t 		*pScreen;
	xcb_window_t 		window;
	xcb_generic_event_t *pEvent;
	xcb_colormap_t 		colormap;
	uint32_t 			mask = 0;
	uint32_t 			values[3];
	uint8_t 			isQuit = 0;

	char title[] = "Heyoooooo!";
	char title_icon[] = "Hello (iconified)";

	Display 			*display;
	int 				default_screen;
	GLXContext 			context;
	GLXFBConfig 		fb_config;
	int 				num_fb_configs = 0;
	XVisualInfo 		*vi;
	GLXDrawable 		drawable;
	GLXWindow 			glxwindow;
	glXCreateContextAttribsARBProc glXCreateContextAttribsARB;
	const char 			*glxExts;

	static int visual_attribs[] = 
	{
		GLX_X_RENDERABLE		, True,
		GLX_DRAWABLE_TYPE		, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE			, GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE		, GLX_TRUE_COLOR,
		GLX_RED_SIZE			, 8,
		GLX_GREEN_SIZE			, 8,
		GLX_BLUE_SIZE			, 8,
		GLX_ALPHA_SIZE			, 8,
		GLX_DEPTH_SIZE			, 24,
		GLX_STENCIL_SIZE		, 8,
		GLX_DOUBLEBUFFER		, True,
		GLX_SAMPLE_BUFFERS		, 1,
		GLX_SAMPLES				, 4,
		None
	};

	subtask_("Opening display")
	{
		int glx_major, glx_minor;
		display = XOpenDisplay(NULL);
		if(!display)
			debug_boom("Display opening failed."); 
		if(!glXQueryVersion(display,&glx_major,&glx_minor)||10*glx_major+glx_minor<13)
			debug_boom("GLX version error.");
		default_screen = DefaultScreen(display);
	}

	subtask_("Finding best matching")
	{
		GLXFBConfig *fb_configs;
		int mx = -1;
		fb_configs = glXChooseFBConfig(display,default_screen,visual_attribs,&num_fb_configs);
		if(!fb_configs||!num_fb_configs)
			debug_boom("GetFBConfig failed.");
		for(int i=0;i<num_fb_configs;i++)
		{
			vi = glXGetVisualFromFBConfig(display,fb_configs[i]);
			if(vi)
			{
				int s_buf, s;
				glXGetFBConfigAttrib(display,fb_configs[i],GLX_SAMPLE_BUFFERS,&s_buf);
				glXGetFBConfigAttrib(display,fb_configs[i],GLX_SAMPLES,&s);
				debug_log("Fbconfig %d, visual ID 0x%lx : SAMPLE_BUFFERS = %d, SAMPLES = %d",i,vi->visualid,s_buf,s);
				if(s_buf&&s>mx) mx = s, fb_config = fb_configs[i];
			}
			XFree(vi);
		}
		vi = glXGetVisualFromFBConfig(display,fb_config);
		debug_log("Matched visual ID = 0x%lx",vi->visualid);
	}

	subtask_("Connecting to XServer")
	{
		pConn = XGetXCBConnection(display);
		if(!pConn)
		{
			XCloseDisplay(display);
			debug_boom("Xcb connection failed.");
		}
		XSetEventQueueOwner(display,XCBOwnsEventQueue);
	}

	subtask_("Finding XCB Screen")
	{
		xcb_screen_iterator_t i = xcb_setup_roots_iterator(xcb_get_setup(pConn));
		for(int j=vi->screen;i.rem&&j>0;j--,xcb_screen_next(&i));
		pScreen = i.data;
	}

	subtask_("Creating window")
	{
		window = pScreen->root;
		// Color
		colormap = xcb_generate_id(pConn);
		xcb_create_colormap(pConn,XCB_COLORMAP_ALLOC_NONE,colormap,window,vi->visualid);
		// Create
		window = xcb_generate_id(pConn);
		mask = XCB_CW_COLORMAP | XCB_CW_EVENT_MASK;
		values[0] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
		values[1] = colormap;
		values[2] = 0;
		xcb_create_window(pConn,XCB_COPY_FROM_PARENT,window,pScreen->root,20,20,640,480,10,XCB_WINDOW_CLASS_INPUT_OUTPUT,vi->visualid,mask,values);
		XFree(vi);
		// Title
		xcb_change_property(pConn,XCB_PROP_MODE_REPLACE,window,XCB_ATOM_WM_NAME,XCB_ATOM_STRING,8,strlen(title),title);
		xcb_change_property(pConn,XCB_PROP_MODE_REPLACE,window,XCB_ATOM_WM_ICON_NAME,XCB_ATOM_STRING,8,strlen(title_icon),title_icon);
		// Map
		xcb_map_window(pConn,window);
		xcb_flush(pConn);
	}

	subtask_("Checking glxExts")
	{
		glxExts = glXQueryExtensionsString(display,default_screen);
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
	}

	subtask_("Creating OpenGL context")
	{
		ctxErrorOccurred = 0;
		int (*oldHandler)(Display*,XErrorEvent*) = XSetErrorHandler(&ctxErrorHandler);
		if(!isExtensionSupported(glxExts,"GLX_ARB_create_context")||!glXCreateContextAttribsARB)
		{
			debug_log("[WARNING] using old-style GLX context");
			context = glXCreateNewContext(display,fb_config,GLX_RGBA_TYPE,0,True);
			if(!context)
				debug_boom("glXCreateNewContext failed.");
		}
		else
		{
			int context_attr[] = {GLX_CONTEXT_MAJOR_VERSION_ARB,3,GLX_CONTEXT_MINOR_VERSION_ARB,0,None};
			context = glXCreateContextAttribsARB(display,fb_config,0,True,context_attr);
			if(!ctxErrorOccurred&&context) debug_log("GL 3.0 context created.");
			else
			{
				XSync(display,False);
				context_attr[1] = 1, context_attr[3] = 0;
				ctxErrorOccurred = 0;
				debug_log("[WARNING] using old-style GLX context");
				context = glXCreateContextAttribsARB(display,fb_config,0,True,context_attr);
			}
		}
		XSync(display,False);
		XSetErrorHandler(oldHandler);
		if(ctxErrorOccurred||!context)
			debug_boom("Failed to create OpenGL context.");
	}

	subtask_("Verifying if the context is direct")
	{
		debug_log(glXIsDirect(display,context)?"Indirect GLX rendering":"Direct GLX rendering");
	}

	subtask_("Creating GLX Window")
	{
		glxwindow = glXCreateWindow(display,fb_config,window,0);
		if(!window)
		{
			xcb_destroy_window(pConn,window);
			glXDestroyContext(display,context);
			debug_boom("glXCreateWindow failed");
		}
		drawable = glxwindow;
		if(!glXMakeContextCurrent(display,drawable,drawable,context))
		{
			xcb_destroy_window(pConn,window);
			glXDestroyContext(display,context);
			debug_boom("glXMakeContextCurrent failed");
		}
	}

	subtask_("Main Loop")
	{
		while(!isQuit&&(pEvent=xcb_wait_for_event(pConn)))
		{
			switch(pEvent->response_type&~0x80)
			{
				case XCB_EXPOSE:
					subtask_("Draw a rect")
					{
						drawSth();
						glXSwapBuffers(display,drawable);
					}
					break;
				case XCB_KEY_PRESS:
					debug_log("Keyboard input detected.");
					isQuit = 1;
					break;
			}
			debug_log("Event detected");
			free(pEvent);
		}
	}

	subtask_("Cleaning up")
	{
		xcb_disconnect(pConn);
	}
	return 0;
}
