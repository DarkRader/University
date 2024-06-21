package cz.cvut.fit.kuznear1.cameraapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import cz.cvut.fit.kuznear1.cameraapp.ui.theme.CameraAppTheme
import cz.cvut.fit.kuznear1.cameraapp.features.camera.presentation.CameraScreen

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            CameraAppTheme {
                CameraScreen()
            }
        }
    }
}
