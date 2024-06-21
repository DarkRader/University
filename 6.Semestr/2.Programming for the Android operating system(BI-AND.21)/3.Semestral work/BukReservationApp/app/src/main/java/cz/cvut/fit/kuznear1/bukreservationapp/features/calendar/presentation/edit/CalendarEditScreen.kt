package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.edit

import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.R
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.AddTopBar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.add.CalendarCreateForm
import org.koin.androidx.compose.koinViewModel

@Composable
fun CalendarEditScreen(
    navController: NavController,
    viewModel: CalendarEditViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    CalendarEditScreen(
        screenState = screenState,
        onNavigateBackClick = { navController.popBackStack() },
        onSubmitClick = viewModel::onSubmitClick,
    )
}

@Composable
private fun CalendarEditScreen(
    screenState: CalendarEditScreenState,
    onNavigateBackClick: () -> Unit,
    onSubmitClick: (Calendar) -> Unit,
) {
    Scaffold(
        topBar = {
            AddTopBar(
                headerText = stringResource(id = R.string.edit),
                onNavigateBackClick = onNavigateBackClick
            )
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer,) {
        Box(modifier = Modifier.padding(it)) {
            screenState.editedCalendar?.let { it1 ->
                CalendarCreateForm(
                    onSubmitClick = onSubmitClick,
                    calendar = it1,
                    collisions = screenState.collisionsCalendar
                )
            }
        }
    }
}