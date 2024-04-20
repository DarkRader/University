package cz.cvut.fit.localstorage

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import cz.cvut.fit.localstorage.profile.DarkMode
import cz.cvut.fit.localstorage.profile.ProfileDataSource
import cz.cvut.fit.localstorage.theme.Lecture7Theme

class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            val darkMode by ProfileDataSource.getDarkModeStream().collectAsStateWithLifecycle(initialValue = DarkMode.System)

            Lecture7Theme(isDarkMode(darkMode = darkMode)) {
                Navigation()
            }
        }
    }

    @Composable
    private fun isDarkMode(darkMode: DarkMode): Boolean {
        return when (darkMode) {
            DarkMode.On -> true
            DarkMode.Off -> false
            DarkMode.System -> isSystemInDarkTheme()
        }
    }
}
