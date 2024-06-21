package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.list

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.R
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.ListTopBar
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import org.koin.androidx.compose.koinViewModel

@Composable
fun CalendarsScreen(
    navController: NavController,
    viewModel: CalendarsViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    LaunchedEffect(Unit) {
        viewModel.updateCalendars()
    }

    CalendarsScreen(
        screenState = screenState,
        onNavigateBackClick = { navController.navigate(Screens.ProfileScreen.route) },
        onAddClick = { navController.navigate(Screens.CalendarAddScreen.route) },
        onCalendarClick = { calendar ->
            navController.navigate(Screens.CalendarDetailScreen.route + "/${calendar.calendar_id}")
        }
    )
}

@Composable
fun CalendarsScreen(
    screenState: CalendarsScreenState,
    onNavigateBackClick: () -> Unit,
    onAddClick: () -> Unit,
    onCalendarClick: (Calendar) -> Unit,
) {
    Scaffold(
        topBar = {
            ListTopBar(
                headerText = stringResource(id = R.string.calendars),
                onNavigateBackClick = onNavigateBackClick,
                onAddClick = onAddClick
            )
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer
    ) { innerPadding ->
        LazyColumn(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding),
            contentPadding = PaddingValues(8.dp),
            verticalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            items(screenState.calendars, key = { it.calendar_id }) { calendar ->
                CalendarCard(
                    calendar = calendar,
                    onClick = { onCalendarClick(calendar) }
                )
            }
        }
    }
}

@Composable
private fun CalendarCard(
    calendar: Calendar,
    onClick: () -> Unit,
) {
    Card(
        modifier = Modifier.clickable(onClick = onClick),
        elevation = CardDefaults.cardElevation(2.dp),
        shape = RoundedCornerShape(16.dp),
        colors = CardDefaults.cardColors(containerColor = MaterialTheme.colorScheme.secondaryContainer)
    ) {
        CalendarItem(
            calendar = calendar,
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp)
        )
    }
}

@Composable
private fun CalendarItem(
    calendar: Calendar,
    modifier: Modifier = Modifier,
) {
    Column(
        modifier
    ) {
       Text(
           text = calendar.reservation_type,
           fontSize = 18.sp,
           fontWeight = FontWeight.Bold,
       )

        Row(
            horizontalArrangement = Arrangement.Start,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text(
                text = stringResource(
                    id = R.string.service_alias,
                    calendar.service_alias
                ) + ",",
                fontSize = 14.sp,
                fontWeight = FontWeight.Normal,
                color = Color.Gray
            )
            Spacer(modifier = Modifier.size(10.dp))
            Text(
                text = stringResource(
                    id = R.string.max_people,
                    calendar.max_people
                ),
                fontSize = 14.sp,
                fontWeight = FontWeight.Normal,
                color = Color.Gray
            )
        }
    }
}