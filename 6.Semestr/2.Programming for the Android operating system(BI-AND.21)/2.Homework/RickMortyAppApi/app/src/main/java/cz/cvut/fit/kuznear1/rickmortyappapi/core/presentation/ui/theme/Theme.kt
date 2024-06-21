package cz.cvut.fit.kuznear1.rickmortyappapi.core.presentation.ui.theme

import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.material3.MaterialTheme
import androidx.compose.runtime.Composable

@Composable
fun RickMortyAppApi(
    darkTheme: Boolean = isSystemInDarkTheme(),
    content: @Composable () -> Unit,
) {
    val colorSchema = if (darkTheme) {
        HomeworkDarkColorSchema
    } else {
        HomeworkLightColorSchema
    }

    MaterialTheme(
        colorScheme = colorSchema,
        typography = Typography,
        content = content,
    )
}
