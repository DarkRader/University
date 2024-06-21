package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.presentation.main_page

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import cz.cvut.fit.kuznear1.bukreservationapp.R
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.Screens
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.presentation.log_in.LoginBottomSheet
import org.koin.androidx.compose.koinViewModel

@Composable
fun ProfileScreen(
    navController: NavController,
    viewModel: ProfileViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()
    val showLoginSheet = remember { mutableStateOf(false) }

    ProfileScreen(
        screenState = screenState,
        onMyReservationClick = {
            navController.navigate(Screens.MyReservationScreen.route)
        },
        onCalendarsClick = {
            navController.navigate(Screens.CalendarsScreen.route)
        },
        onMiniServicesClick = {
            navController.navigate(Screens.MiniServicesScreen.route)
        },
        onLogInClick =  { showLoginSheet.value = true }
    )

    if (showLoginSheet.value) {
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
fun ProfileScreen(
    screenState: ProfileScreensState,
    onMyReservationClick: () -> Unit,
    onCalendarsClick: () -> Unit,
    onMiniServicesClick: () -> Unit,
    onLogInClick: () -> Unit
) {
    Scaffold(
        topBar = {
            CustomTopBar(
                screenState = screenState,
                onLogInClick = onLogInClick
            )
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer,
    ) { innerPadding ->
        LazyColumn(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding),
            contentPadding = PaddingValues(8.dp),
            verticalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            item {
                ProfileCard(
                    onMyReservationClick = onMyReservationClick,
                    onCalendarsClick = onCalendarsClick,
                    onMiniServicesClick = onMiniServicesClick,
                )
            }
        }
    }
}

@Composable
private fun CustomTopBar(
    screenState: ProfileScreensState,
    onLogInClick: () -> Unit
) {
    Column {
        TopAppBar(
            title = {
                if(screenState.username == null) {
                    Row(
                        modifier = Modifier.fillMaxWidth(),
                        horizontalArrangement = Arrangement.SpaceBetween
                    ) {
                        Text(
                            text = stringResource(id = R.string.buk_res),
                            style = MaterialTheme.typography.headlineMedium,
                            color = MaterialTheme.colorScheme.onPrimary,
                            modifier = Modifier.align(Alignment.CenterVertically)
                        )
                    }

                    Spacer(modifier = Modifier.weight(1f))

                    Row(
                        modifier = Modifier
                            .fillMaxWidth()
                            .padding(end = 16.dp),
                        horizontalArrangement = Arrangement.End
                    ) {
                        Text(
                            modifier = Modifier
                                .clickable { onLogInClick() }
                                .align(Alignment.CenterVertically),
                            text = stringResource(id = R.string.log_in),
                            style = MaterialTheme.typography.headlineMedium,
                            color = MaterialTheme.colorScheme.onPrimary
                        )
                    }
                } else {
                    Text(
                        text = stringResource(id = R.string.loggined,
                            screenState.username),
                        style = MaterialTheme.typography.headlineMedium,
                        color = MaterialTheme.colorScheme.onPrimary,
                    )
                }
            },
            colors = TopAppBarDefaults.topAppBarColors(
                containerColor = MaterialTheme.colorScheme.primaryContainer
            )
        )
        HorizontalDivider(
            modifier = Modifier.fillMaxWidth(),
            thickness = 1.dp,
            color = MaterialTheme.colorScheme.onPrimary
        )
    }
}

@Composable
private fun ProfileCard(
    onMyReservationClick: () -> Unit,
    onCalendarsClick: () -> Unit,
    onMiniServicesClick: () -> Unit,
) {
    CardProperty(
        onClick = onMyReservationClick,
        header = stringResource(id = R.string.my_reservation)
    )

    Spacer(modifier = Modifier.padding(50.dp))

    CardProperty(
        onClick = onCalendarsClick,
        header = stringResource(id = R.string.calendars)
    )

    Spacer(modifier = Modifier.padding(4.dp))

    CardProperty(
        onClick = onMiniServicesClick,
        header = stringResource(id = R.string.mini_services)
    )
}

@Composable
private fun CardProperty(
    onClick: () -> Unit,
    header: String
) {
    Card(
        modifier = Modifier.clickable(onClick = onClick),
        elevation = CardDefaults.cardElevation(2.dp),
        shape = RoundedCornerShape(16.dp),
        colors = CardDefaults.cardColors(containerColor = MaterialTheme.colorScheme.primary)
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp),
            horizontalArrangement = Arrangement.Center,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text(
                text = header,
                fontSize = 20.sp,
                fontWeight = FontWeight.Bold,
            )
        }
    }
}