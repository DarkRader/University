package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.reservation

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyRow
import androidx.compose.foundation.lazy.items
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.SuggestionChip
import androidx.compose.material3.SuggestionChipDefaults
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.R
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.ReservationChip

@Composable
fun ReservationScreen(
    navController: NavController,
    viewModel: ReservationViewModel = viewModel(),
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    ReservationScreen(
        screenState = screenState,
        onAddReservationClick = { alias ->
            navController.navigate(Screens.FormScreen.route + "/${alias}")
        },
        onReservationChipClick = viewModel::onReservationChipClick,
    )
}

@Composable
private fun ReservationScreen(
    screenState: ReservationScreenState,
    onAddReservationClick: (String) -> Unit,
    onReservationChipClick: (String, String) -> Unit,
) {
    var calendarType by remember { mutableStateOf(screenState.serviceAlias) }

    LaunchedEffect(screenState.serviceAlias) {
        calendarType = screenState.serviceAlias
    }

    Scaffold(
        topBar = {
            CustomTopAppBar(
                screenState = screenState,
                onAddReservationClick = onAddReservationClick,
                onReservationChipClick = { newCurrentReservation, newServiceAlias ->
                    onReservationChipClick(newCurrentReservation, newServiceAlias)
                    calendarType = newCurrentReservation
                }
            )
        },
        containerColor = MaterialTheme.colorScheme.secondaryContainer,
    ) { innerPadding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding)
                .padding(8.dp)
        ) {
            CalendarWebView(calendarType)
        }
    }
}

@Composable
private fun CustomTopAppBar(
    screenState: ReservationScreenState,
    onAddReservationClick: (String) -> Unit,
    onReservationChipClick: (String, String) -> Unit,
) {
    Column {
        TopAppBar(
            title = {
                Text(
                    text = stringResource(id = R.string.create_reservation,
                        screenState.chosenReservation),
                    style = MaterialTheme.typography.headlineMedium,
                    color = MaterialTheme.colorScheme.onPrimary
                )
            },
            actions = {
                IconButton(onClick = { onAddReservationClick(screenState.serviceAlias) }) {
                    Icon(
                        Icons.Default.Add,
                        contentDescription = stringResource(id = R.string.add_button),
                    )
                }
            },
            colors = TopAppBarDefaults.topAppBarColors(
                containerColor = MaterialTheme.colorScheme.secondaryContainer
            )
        )
        LazyRow(
            modifier = Modifier
                .fillMaxWidth()
                .padding(top = 4.dp)
        ) {
            items(screenState.reservations) { reservation ->
                ReservationChip(
                    reservationChip = reservation,
                    currentReservation = screenState.chosenReservation,
                    onReservationChipClick = onReservationChipClick,
                    )
            }
        }
        HorizontalDivider(
            modifier = Modifier.fillMaxWidth(),
            thickness = 1.dp,
            color = MaterialTheme.colorScheme.onPrimary
        )
    }
}

@Composable
fun ReservationChip(
    reservationChip: ReservationChip,
    currentReservation: String,
    onReservationChipClick: (String, String) -> Unit,
) {
    val backgroundColor = if (reservationChip.reservationService == currentReservation) {
        reservationChip.chooseColor
    } else {
        reservationChip.backgroundColor
    }

    SuggestionChip(
        modifier = Modifier.padding(4.dp),
        onClick = {
            onReservationChipClick(reservationChip.reservationService,
                reservationChip.serviceAlias)
        },
        label = {
            Text(text = reservationChip.reservationService)
        },
        colors = SuggestionChipDefaults.suggestionChipColors(
            containerColor = backgroundColor,
            labelColor = MaterialTheme.colorScheme.onPrimary
        ),
        border = SuggestionChipDefaults.suggestionChipBorder(
            enabled = true,
            borderColor = MaterialTheme.colorScheme.onPrimary,
            borderWidth = 1.dp
        )
    )
}