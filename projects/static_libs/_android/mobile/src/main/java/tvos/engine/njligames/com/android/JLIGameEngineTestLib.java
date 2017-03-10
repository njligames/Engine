package tvos.engine.njligames.com.android;

import java.util.ArrayList;
import java.util.Vector;

//import android.content.res.AssetManager;
//import android.view.MotionEvent;
//import android.view.MotionEvent.PointerCoords;

public class JLIGameEngineTestLib {
	static {

		/*
		// Try debug libraries...
    	try { System.loadLibrary("fmodD");
    		  System.loadLibrary("fmodstudioD"); }
    	catch (UnsatisfiedLinkError e) { }
    	// Try logging libraries...
    	try { System.loadLibrary("fmodL");
    		  System.loadLibrary("fmodstudioL"); }
    	catch (UnsatisfiedLinkError e) { }
		// Try release libraries...
		try { System.loadLibrary("fmod");
		      System.loadLibrary("fmodstudio"); }
		catch (UnsatisfiedLinkError e) { }
		*/

		System.loadLibrary("stlport_shared");
		System.loadLibrary("native-lib");
    }

	public static native void create();
	
	/**
	 * 
	 * @param x the current view x position
	 * @param y the current view y position
	 * @param width the current view width
	 * @param height the current view height
	 */
	public static native void resize(int x, int y, int width, int height);
	
	/**
	 * 
	 * @param step
	 */
	public static native void update(float step);
	
	public static native void render();
	
	public static native void destroy();
	
	public static native void pause();
	
	public static native void unpause();
	
//	public static native void initAssetManager(AssetManager assetManager);
//
//	public static native void onTouchDown(ArrayList<MotionEvent.PointerCoords> e);
//	public static native void onTouchUp(ArrayList<MotionEvent.PointerCoords> e);
//	public static native void onTouchMove(ArrayList<MotionEvent.PointerCoords> e);
//	public static native void onTouchCancel(ArrayList<MotionEvent.PointerCoords> e);
}
