package cz.cvut.kuznear1.dogapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import cz.cvut.kuznear1.dogapp.core.presentation.ui.Navigation
import cz.cvut.kuznear1.dogapp.core.presentation.ui.theme.DogAppTheme

class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            DogAppTheme {
                Navigation()
            }
        }
    }
}