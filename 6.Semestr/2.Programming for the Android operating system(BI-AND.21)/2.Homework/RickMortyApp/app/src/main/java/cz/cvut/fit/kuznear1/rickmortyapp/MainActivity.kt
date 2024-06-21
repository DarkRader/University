package cz.cvut.fit.kuznear1.rickmortyapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import cz.cvut.fit.kuznear1.rickmortyapp.ui.theme.RickMortyAppTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            RickMortyAppTheme {
                Navigation()
            }
        }
    }
}