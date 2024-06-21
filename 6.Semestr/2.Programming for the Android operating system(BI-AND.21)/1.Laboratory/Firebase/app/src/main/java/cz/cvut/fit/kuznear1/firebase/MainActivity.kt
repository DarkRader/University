package cz.cvut.fit.kuznear1.firebase

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.isSystemInDarkTheme
import cz.cvut.fit.kuznear1.firebase.core.presentation.theme.Lecture10Theme

class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            Lecture10Theme(isSystemInDarkTheme()) {
                Navigation()
            }
        }
    }
}
