package cz.cvut.kuznear1.footballapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import cz.cvut.kuznear1.footballapp.ui.theme.FootballAppTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            FootballAppTheme {
                Navigation()
            }
        }
    }
}
