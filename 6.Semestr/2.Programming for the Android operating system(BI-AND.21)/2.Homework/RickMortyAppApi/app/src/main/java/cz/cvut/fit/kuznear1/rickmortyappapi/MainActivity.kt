package cz.cvut.fit.kuznear1.rickmortyappapi

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui.MainScreen
import cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui.theme.RickMortyAppApi

class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            RickMortyAppApi {
                MainScreen()
            }
        }
    }
}
