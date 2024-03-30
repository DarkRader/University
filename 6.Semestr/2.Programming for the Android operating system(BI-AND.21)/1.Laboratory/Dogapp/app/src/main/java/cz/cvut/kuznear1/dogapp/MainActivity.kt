package cz.cvut.kuznear1.dogapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.runtime.getValue
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import cz.cvut.kuznear1.dogapp.ui.theme.DogAppTheme

class MainActivity : ComponentActivity() {

    private val viewModel: MainViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            DogAppTheme {
                val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()
                MainScreen(
                    screenState = screenState,
                    onGetDogFactsClick = { viewModel.onGetDogFactsClick() },
                    onLimitTextChange = { viewModel.onLimitTextChange(it) }
                )
            }
        }
    }
}