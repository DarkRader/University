package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.add

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
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.CustomDropBox
import cz.cvut.fit.kuznear1.bukreservationapp.core.presentation.ui.FieldTextString
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import org.koin.androidx.compose.koinViewModel

@Composable
fun MiniServiceAddScreen(
    navController: NavController,
    viewModel: MiniServiceAddViewModel = koinViewModel(),
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    MiniServiceAddScreen(
        screenState = screenState,
        onNavigateBackClick = { navController.popBackStack() },
        onSubmitClick = viewModel::onSubmitClick,
    )
}

@Composable
private fun MiniServiceAddScreen(
    screenState: MiniServiceAddScreenState,
    onNavigateBackClick: () -> Unit,
    onSubmitClick: (MiniServiceRequest) -> Unit,
) {
    Scaffold(
        topBar = {
            AddTopBar(
                headerText = "Add New Mini Service",
                onNavigateBackClick = onNavigateBackClick
            )
        },
        containerColor = MaterialTheme.colorScheme.primaryContainer,) {
        Box(modifier = Modifier.padding(it)) {
            MiniServiceAddFields(
                miniService = screenState.newMiniService ?: MiniServiceRequest("", ""),
                onSubmitClick = onSubmitClick,
            )
        }
    }
}

@Composable
fun MiniServiceAddFields(
    miniService: MiniServiceRequest,
    onSubmitClick: (MiniServiceRequest) -> Unit,
) {
    val newMiniService = remember { mutableStateOf(miniService) }
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
                    .fillMaxWidth(fraction = 2 / 3f)
                    .padding(horizontal = 16.dp, vertical = 16.dp),
                verticalArrangement = Arrangement.spacedBy(14.dp),
            ) {
                FieldTextString(
                    header = "Name:",
                    body = "Write name",
                    text = newMiniService.value.name,
                    onTextChanged = { newMiniService.value = newMiniService.value.copy(name = it) }
                )

                CustomDropBox(
                    header = "Server alias:",
                    body = "Choose alias",
                    chosenOption = newMiniService.value.service_alias,
                    onTextChanged = { newMiniService.value = newMiniService.value.copy(service_alias = it) },
                    options = listOf("klub", "stud", "grill")
                )

                Button(onClick = {
                    onSubmitClick(newMiniService.value)
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