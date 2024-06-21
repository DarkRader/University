package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.detail

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.DetailTopBar
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.TextHeaderStyle
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.TextSecondHeader
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.ApiCalendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import org.koin.androidx.compose.koinViewModel

@Composable
fun CalendarDetailScreen(
    navController: NavController,
    viewModel: CalendarDetailViewModel = koinViewModel(),
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    LaunchedEffect(Unit) {
        viewModel.updateCalendar()
    }

    CalendarDetailScreen(
        screenState = screenState,
        findTypeById = viewModel::findCalendarTypeByID,
        onEditClick = { calendar ->
            navController.navigate(Screens.CalendarEditScreen.route + "/${calendar.calendar_id}")
        },
        onDeleteClick = viewModel::deleteCalendar,
        onNavigateBackClick = { navController.popBackStack() },
    )
}

@Composable
private fun CalendarDetailScreen(
    screenState: CalendarDetailScreenState,
    findTypeById: (String) -> String,
    onEditClick: (Calendar) -> Unit,
    onDeleteClick: () -> Unit,
    onNavigateBackClick: () -> Unit,
) {
    screenState.calendar?.let { calendar ->
        Scaffold(
            topBar = {
                DetailTopBar(
                    headerText = calendar.reservation_type,
                    onEditClick = { onEditClick(calendar) },
                    onDeleteClick = onDeleteClick,
                    onNavigateBackClick = onNavigateBackClick,
                )
            },
            containerColor = MaterialTheme.colorScheme.primaryContainer
        ) {
            Box(modifier = Modifier.padding(it)) {
                CalendarDetail(
                    findTypeById = findTypeById,
                    calendar = calendar
                )
            }
        }
    }

}

@Composable
private fun CalendarDetail(
    findTypeById: (String) -> String,
    calendar: Calendar
) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
    ) {
        Card(
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp),
            elevation = CardDefaults.cardElevation(2.dp),
            shape = RoundedCornerShape(16.dp),
            colors = CardDefaults.cardColors(containerColor = MaterialTheme.colorScheme.secondaryContainer)
        ) {
            Column(
                modifier = Modifier
                    .padding(horizontal = 16.dp, vertical = 16.dp),
                verticalArrangement = Arrangement.spacedBy(14.dp),
            ) {
                TextHeaderStyle(calendar.reservation_type, "Reservation type:")
                TextHeaderStyle(calendar.event_name, "Event name:")
                TextHeaderStyle(calendar.service_alias, "Server alias:")
                TextHeaderStyle(calendar.max_people, "Max people:")
                TextHeaderStyle(calendar.collision_with_itself, "Collision with itself:")

                Column {
                    TextSecondHeader("Collision with calendars:")

                    calendar.collision_with_calendar.forEachIndexed() { ind, type ->
                        val isLast = ind == calendar.collision_with_calendar.size - 1
                        Row {
                            Text(
                                text = findTypeById(type),
                                style = MaterialTheme.typography.bodyMedium,
                                color = MaterialTheme.colorScheme.onSecondary,
                            )
                            if (!isLast) {
                                Text(text = ",")
                                Spacer(modifier = Modifier.width(8.dp))
                            }
                        }
                    }
                }

                TextMemberRules(calendar.club_member_rules, "Club Member Rules:")
                TextMemberRules(calendar.active_member_rules, "Active Member Rules:")
                TextMemberRules(calendar.manager_rules, "Manager Rules:")
            }
        }
    }
}

@Composable
private fun TextMemberRules(
    rules: ApiCalendar.MemberRules,
    header: String
) {
    Text(
        text = header,
        style = MaterialTheme.typography.headlineMedium,
        color = MaterialTheme.colorScheme.primary,
    )

    Column(
        modifier = Modifier
            .padding(horizontal = 32.dp),
        verticalArrangement = Arrangement.spacedBy(14.dp),
    ) {
        TextHeaderStyle(rules.night_time, "Night time:")
        TextHeaderStyle(rules.reservation_more_24_hours, "Reservation more 24 hours:")
        TextHeaderStyle(rules.in_advance_day, "Prior day:")
        TextHeaderStyle(rules.in_advance_hours, "Advance hour:")
        TextHeaderStyle(rules.in_advance_minutes, "Advance minute:")
    }
}