package tvos.engine.njligames.com.android;

import java.util.Vector;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.MotionEvent.PointerCoords;
import android.view.View.OnTouchListener;


public class MainActivity extends Activity {

    GLView glSurfaceView;

    @Override protected void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);

        //JLIGameEngineTestLib.initAssetManager(getAssets());

        glSurfaceView = new GLView(getApplication());
        setContentView(glSurfaceView);
//        org.fmod.FMOD.init(this);
    }

    @Override protected void onPause() {
        super.onPause();
        glSurfaceView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        glSurfaceView.onResume();
    }

    @Override
    protected void onDestroy()
    {
//        org.fmod.FMOD.close();

        super.onDestroy();
    }
}




//
//
//import android.support.v7.app.AppCompatActivity;
//import android.os.Bundle;
//import android.widget.TextView;
//import android.opengl.GLSurfaceView;
//
//public class MainActivity extends AppCompatActivity {
//
//    private GLSurfaceView mGLView;
//
//    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
//
//        // Example of a call to a native method
//        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());
//
//        // Create a GLSurfaceView instance and set it
//        // as the ContentView for this Activity
//        mGLView = new MyGLSurfaceView(this);
//        setContentView(mGLView);
//    }
//
//    @Override
//    protected void onPause() {
//        super.onPause();
//        // The following call pauses the rendering thread.
//        // If your OpenGL application is memory intensive,
//        // you should consider de-allocating objects that
//        // consume significant memory here.
//        mGLView.onPause();
//    }
//
//    @Override
//    protected void onResume() {
//        super.onResume();
//        // The following call resumes a paused rendering thread.
//        // If you de-allocated graphic objects for onPause()
//        // this is a good place to re-allocate them.
//        mGLView.onResume();
//    }
//
//    /**
//     * A native method that is implemented by the 'native-lib' native library,
//     * which is packaged with this application.
//     */
//    public native String stringFromJNI();
//}
