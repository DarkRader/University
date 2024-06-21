package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.presentation.add

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.R
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.AddTopBar
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.CheckBoxList
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.CustomCheckBox
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.CustomDropBox
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.FieldTextInt
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.FieldTextString
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.TextSecondHeader
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.ApiCalendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import org.koin.androidx.compose.koinViewModel

@Composable
fun CalendarAddScreen(
    navController: NavController,
    viewModel: CalendarAddViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    CalendarAddScreen(
        screenState = screenState,
        onNavigateBackClick = { navController.popBackStack() },
        onSubmitClick = viewModel::onSubmitClick,
    )
}

@Composable
private fun CalendarAddScreen(
    screenState: CalendarAddScreenState,
    onNavigateBackClick: () -> Unit,
    onSubmitClick: (Calendar) -> Unit,
) {
    Scaffold(
        topBar = {
            AddTopBar(
                headerText = "Add New Calendar",
                onNavigateBackClick = onNavigateBackClick
            )
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer,) {
        Box(modifier = Modifier.padding(it)) {
            CalendarCreateForm(
                onSubmitClick = onSubmitClick,
                calendar = screenState.newCalendar,
                collisions = screenState.collisionsCalendar
            )
        }
    }
}

@Composable
fun CalendarCreateForm(
    onSubmitClick: (Calendar) -> Unit,
    calendar: Calendar,
    collisions: List<Calendar>
) {
    val newCalendar = remember {mutableStateOf(calendar)}
    val selectedItems = remember { mutableStateOf(newCalendar.value.collision_with_calendar) }
    val creationSuccessful = remember { mutableStateOf(false) }

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
                FieldTextString(
                    header = "Calendar ID:",
                    body = "Write id from google calendar",
                    text = newCalendar.value.calendar_id,
                    onTextChanged = { newCalendar.value = newCalendar.value.copy(calendar_id = it) }
                )

                FieldTextString(
                    header = "Reservation type:",
                    body = "Write reservation type",
                    text = newCalendar.value.reservation_type,
                    onTextChanged = { newCalendar.value = newCalendar.value.copy(reservation_type = it) }
                )

                FieldTextString(
                    header = "Event name:",
                    body = "Write event name",
                    text = newCalendar.value.event_name,
                    onTextChanged = { newCalendar.value = newCalendar.value.copy(event_name = it) }
                )


                CustomDropBox(
                    header = "Server alias:",
                    body = "Choose alias",
                    chosenOption = newCalendar.value.service_alias,
                    onTextChanged = { newCalendar.value = newCalendar.value.copy(service_alias = it) },
                    options = listOf("klub", "stud", "grill")
                )

                FieldTextInt(
                    header = "Max people:",
                    body = "Write max people",
                    number = newCalendar.value.max_people,
                    onNumberChanged = { newCalendar.value = newCalendar.value.copy(max_people = it) }
                )


                TextSecondHeader("Collision with itself:")
                CustomCheckBox(
                    text = "This calendar have collision with itself",
                    checked = newCalendar.value.collision_with_itself,
                    onCheckedChange = { newCalendar.value = newCalendar.value.copy(collision_with_itself = it) }
                )

                TextSecondHeader("Collision with other calendars:")
                CheckBoxList(
                    items = collisions,
                    selectedItems = selectedItems.value,
                    onItemCheckedChange = { item, isChecked ->
                        val newSelectedItems = if (isChecked) {
                            selectedItems.value + item
                        } else {
                            selectedItems.value - item
                        }
                        selectedItems.value = newSelectedItems
                        newCalendar.value = newCalendar.value.copy(collision_with_calendar = newSelectedItems)
                    }
                )

                FileMemberRules(
                    memberRules = newCalendar.value.club_member_rules,
                    onMemberRulesChanged = { newMemberRules ->
                          newCalendar.value = newCalendar.value.copy(club_member_rules = newMemberRules)
                    },
                    header = "Club Member Rules:"
                )
                FileMemberRules(
                    memberRules = newCalendar.value.active_member_rules,
                    onMemberRulesChanged = { newMemberRules ->
                        newCalendar.value = newCalendar.value.copy(active_member_rules = newMemberRules)
                    },
                    header = "Active Member Rules:"
                )
                FileMemberRules(
                    memberRules = newCalendar.value.manager_rules,
                    onMemberRulesChanged = { newMemberRules ->
                        newCalendar.value = newCalendar.value.copy(manager_rules = newMemberRules)
                    },
                    header = "Manager Rules:"
                )


                Button(onClick = {
                    onSubmitClick(newCalendar.value)
                    creationSuccessful.value = true
                },  ) {
                    Text(
                        text = stringResource(id = R.string.submit),
                        style = MaterialTheme.typography.headlineSmall,
                        color = MaterialTheme.colorScheme.onPrimary
                    )
                }

                if (creationSuccessful.value) {
                    Text(
                        text = stringResource(id = R.string.successful),
                        style = MaterialTheme.typography.headlineSmall,
                        color = MaterialTheme.colorScheme.onPrimary
                    )
                }
            }
        }
    }
}

@Composable
private fun FileMemberRules(
    memberRules: ApiCalendar.MemberRules,
    onMemberRulesChanged: (ApiCalendar.MemberRules) -> Unit,
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
        TextSecondHeader("Night time:")
        CustomCheckBox(
            text = "Enabled",
            checked = memberRules.night_time,
            onCheckedChange = { onMemberRulesChanged(memberRules.copy(night_time = it)) }
        )

        TextSecondHeader("Reservation more 24 hours:")
        CustomCheckBox(
            text = "Enabled",
            checked = memberRules.reservation_more_24_hours,
            onCheckedChange = { onMemberRulesChanged(memberRules.copy(reservation_more_24_hours = it))  }
        )

        FieldTextInt(
            header = "Prior day:",
            body = "Write prior day",
            number = memberRules.in_advance_day,
            onNumberChanged = { onMemberRulesChanged(memberRules.copy(in_advance_day = it))  }
        )

        FieldTextInt(
            header = "Advance hour:",
            body = "Write advance hour",
            number = memberRules.in_advance_hours,
            onNumberChanged = { onMemberRulesChanged(memberRules.copy(in_advance_hours = it))  }
        )

        FieldTextInt(
            header = "Advance minute:",
            body = "Write advance minute",
            number = memberRules.in_advance_minutes,
            onNumberChanged = { onMemberRulesChanged(memberRules.copy(in_advance_minutes = it))  }
        )
    }
}