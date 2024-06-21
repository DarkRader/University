package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.presentation.form

import android.app.DatePickerDialog
import android.app.TimePickerDialog
import android.widget.DatePicker
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ArrowBack
import androidx.compose.material.icons.filled.DateRange
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.R
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.CheckBoxListString
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.CustomDropBox
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.FieldTextInt
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.FieldTextString
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.TextSecondHeader
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.presentation.log_in.LoginBottomSheet
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.CreateEvent
import org.koin.androidx.compose.koinViewModel
import java.util.Calendar
import java.util.Date

@Composable
fun FormScreen(
    navController: NavController,
    viewModel: FormViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()
    val showLoginSheet = remember { mutableStateOf(screenState.notLogin) }

    FormScreen(
        screenState = screenState,
        onSubmitClick = viewModel::onSubmitClick,
        onNavigateBackClick = { navController.popBackStack() },
        whenTypeChosen = viewModel::whenTypeChosen
    )

    if (screenState.notLogin) {
        LoginBottomSheet(
            onDismissRequest = { showLoginSheet.value = false },
            onCodeReceived = { code ->
                viewModel.onReceivedCode(code)
                showLoginSheet.value = false
            }
        )
    }
}

@Composable
private fun FormScreen(
    screenState: FormScreenState,
    onSubmitClick: (CreateEvent) -> Unit,
    onNavigateBackClick: () -> Unit,
    whenTypeChosen: (String) -> Unit
) {
    Scaffold(
        topBar = {
            Column {
                TopAppBar(
                    navigationIcon = {
                        IconButton(onClick = onNavigateBackClick) {
                            Icon(
                                Icons.AutoMirrored.Filled.ArrowBack,
                                contentDescription = stringResource(id = R.string.back_button),
                                tint = MaterialTheme.colorScheme.onPrimary,
                            )
                        }
                    },
                    title = {
                        Row(
                            modifier = Modifier
                                .padding(4.dp)
                        ) {
                            Text(
                                text = stringResource(id = R.string.reservation_form),
                                style = MaterialTheme.typography.headlineMedium,
                                color = MaterialTheme.colorScheme.onPrimary
                            )
                            Spacer(modifier = Modifier.padding(4.dp))
                            Icon(
                                Icons.Default.DateRange,
                                contentDescription = stringResource(id = R.string.select_start_date),
                                tint = MaterialTheme.colorScheme.onPrimary
                            )
                        }
                    },
                    colors = TopAppBarDefaults.topAppBarColors(
                        containerColor = MaterialTheme.colorScheme.secondaryContainer
                    )
                )
                HorizontalDivider(
                    modifier = Modifier.fillMaxWidth(),
                    thickness = 1.dp,
                    color = MaterialTheme.colorScheme.onPrimary
                )
            }
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer,
    ) { innerPadding ->
        Box(modifier = Modifier.padding((innerPadding))) {
            FormDetail(
                onSubmitClick = onSubmitClick,
                screenState = screenState,
                whenTypeChosen = whenTypeChosen
            )
        }
    }
}

@Composable
private fun FormDetail(
    onSubmitClick: (CreateEvent) -> Unit,
    screenState: FormScreenState,
    whenTypeChosen: (String) -> Unit
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
            shape = RoundedCornerShape(16.dp),
            colors = CardDefaults.cardColors(containerColor = MaterialTheme.colorScheme.secondaryContainer),
            elevation = CardDefaults.cardElevation(2.dp)
        ) {
            Column(
                modifier = Modifier
                    .padding(horizontal = 16.dp, vertical = 16.dp),
                verticalArrangement = Arrangement.spacedBy(14.dp)
            ) {
                FormCardDetail(
                    onSubmitClick = onSubmitClick,
                    screenState = screenState,
                    whenTypeChosen = whenTypeChosen
                )
            }
        }
    }
}

@Composable
private fun FormCardDetail(
    onSubmitClick: (CreateEvent) -> Unit,
    screenState: FormScreenState,
    whenTypeChosen: (String) -> Unit
) {
    val newEvent = remember { mutableStateOf(screenState.event) }
    val creationSuccessful = remember { mutableStateOf(false) }

    val reservationTypes: MutableList<String> = mutableListOf()
    screenState.reservationTypes.forEach { calendar ->
        reservationTypes.add(calendar.reservation_type)
    }

    FormFields("Reservation Date:") {
        DatePicker { date ->
            val currentStartTime = newEvent.value.start_datetime.split("T").getOrElse(1) { "00:00" }
            val currentEndTime = newEvent.value.start_datetime.split("T").getOrElse(1) { "00:00" }
            newEvent.value = newEvent.value.copy(
                start_datetime = "${date}T${currentStartTime}",
                end_datetime = "${date}T${currentEndTime}"
            )
        }
    }
    FormFields("Start Reservation Time:") {
        TimePicker { time ->
            val currentDate = newEvent.value.start_datetime.split("T").getOrElse(0) { "2024-06-05" }
            newEvent.value = newEvent.value.copy(start_datetime = "${currentDate}T${time}")
        }
    }
    FormFields("End Reservation Time:") {
        TimePicker { time ->
            val currentDate = newEvent.value.end_datetime.split("T").getOrElse(0) { "2024-06-05" }
            newEvent.value = newEvent.value.copy(end_datetime = "${currentDate}T${time}")
        }
    }

    FieldTextString(
        body = "Write the purpose",
        header = "Purpose:",
        text = newEvent.value.purpose,
        onTextChanged = { newEvent.value = newEvent.value.copy(purpose = it) }
    )

    FieldTextInt(
        body = "Write number",
        header = "Number of Guests:",
        number = newEvent.value.guests,
        onNumberChanged = { newEvent.value = newEvent.value.copy(guests = it) }
    )

    FieldTextString(
        body = "Write your email",
        header = "Email:",
        text = newEvent.value.email,
        onTextChanged = { newEvent.value = newEvent.value.copy(email = it) }
    )

    CustomDropBox(
        header = "Reservation Type:",
        body = "Choose type",
        chosenOption = newEvent.value.reservation_type,
        onTextChanged = { newEvent.value = newEvent.value.copy(reservation_type = it) },
        options = reservationTypes
    )

    if(newEvent.value.reservation_type != "") {
        whenTypeChosen(newEvent.value.reservation_type)

        if(screenState.chosenType.mini_services != null) {
            val selectedItems = remember { mutableStateOf(screenState.chosenType.mini_services) }

            TextSecondHeader("Additional Services:")
            CheckBoxListString(
                items = screenState.chosenType.mini_services,
                selectedItems = selectedItems.value,
                onItemCheckedChange = { item, isChecked ->
                    val newSelectedItems = if (isChecked) {
                        selectedItems.value + item
                    } else {
                        selectedItems.value - item
                    }
                    selectedItems.value = newSelectedItems
                    newEvent.value = newEvent.value.copy(additional_services = newSelectedItems)
                }
            )
        }
    }

    Button(onClick = {
        onSubmitClick(newEvent.value)
        creationSuccessful.value = true
    },  ) {
        Text(
            text = stringResource(id = R.string.submit),
            style = MaterialTheme.typography.headlineSmall,
            color = MaterialTheme.colorScheme.onPrimary
        )
    }

    if (creationSuccessful.value) {
        if(screenState.warningMessage == "") {
            Text(
                text = stringResource(id = R.string.successful),
                style = MaterialTheme.typography.headlineSmall,
                color = MaterialTheme.colorScheme.onPrimary
            )
        } else if(screenState.notLogin) {
            Text(
                text = stringResource(id = R.string.you_need_log_in),
                style = MaterialTheme.typography.headlineSmall,
                color = MaterialTheme.colorScheme.onPrimary
            )
        } else {
            Text(
                text = screenState.warningMessage,
                style = MaterialTheme.typography.headlineSmall,
                color = MaterialTheme.colorScheme.onPrimary
            )
        }
    }

}

@Composable
private fun FormFields(
    fieldName: String,
    fieldContent: @Composable () -> Unit,
) {
    Column {
        TextSecondHeader(header = fieldName)
        fieldContent()
    }
}

@Suppress("NAME_SHADOWING")
@Composable
private fun DatePicker(
    onDateSelected: (String) -> Unit
){

    val mContext = LocalContext.current

    val mYear: Int
    val mMonth: Int
    val mDay: Int

    val mCalendar = Calendar.getInstance()

    mYear = mCalendar.get(Calendar.YEAR)
    mMonth = mCalendar.get(Calendar.MONTH)
    mDay = mCalendar.get(Calendar.DAY_OF_MONTH)

    mCalendar.time = Date()

    val initialDate = "${mDay}/${mMonth + 1}/$mYear"
    val mDate = remember { mutableStateOf(initialDate) }

    val mDatePickerDialog = DatePickerDialog(
        mContext,
        { _: DatePicker, mYear: Int, mMonth: Int, mDayOfMonth: Int ->
            val selectedDate = String.format("%04d-%02d-%02d", mYear, mMonth + 1, mDayOfMonth)
            mDate.value = "$mDayOfMonth/${mMonth+1}/$mYear"
            onDateSelected(selectedDate)
        }, mYear, mMonth, mDay
    )

    BoxPicker(
        onClick = { mDatePickerDialog.show() },
        mTime = mDate.value
    )
}

@Suppress("NAME_SHADOWING")
@Composable
private fun TimePicker(
    onTimeSelected: (String) -> Unit
){

    val mContext = LocalContext.current

    val mCalendar = Calendar.getInstance()
    val mHour = mCalendar[Calendar.HOUR_OF_DAY]
    val mMinute = mCalendar[Calendar.MINUTE]

    val initialTime = String.format("%02d:%02d", mHour, mMinute)
    val mTime = remember { mutableStateOf(initialTime) }

    val mTimePickerDialog = TimePickerDialog(
        mContext,
        {_, mHour: Int, mMinute: Int ->
            val selectedTime = String.format("%02d:%02d", mHour, mMinute)
            mTime.value = selectedTime
            onTimeSelected(selectedTime)
        }, mHour, mMinute, true
    )
    
    BoxPicker(
        onClick = { mTimePickerDialog.show() },
        mTime = mTime.value
    )
}

@Composable
private fun BoxPicker(
    onClick: () -> Unit,
    mTime: String
) {
    Box(
        modifier = Modifier
            .clickable(onClick = onClick)
            .clip(CircleShape)
            .background(MaterialTheme.colorScheme.secondaryContainer)
            .padding(start = 16.dp)
    ) {
        Text(
            text = mTime,
            style = MaterialTheme.typography.bodyLarge,
            color = MaterialTheme.colorScheme.onPrimary
        )
    }
}
