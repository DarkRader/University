package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.edit

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
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.presentation.add.MiniServiceAddFields
import org.koin.androidx.compose.koinViewModel

@Composable
fun MiniServiceEditScreen(
    navController: NavController,
    viewModel: MiniServiceEditViewModel = koinViewModel()
) {
    val screenState by viewModel.screenStateStream.collectAsStateWithLifecycle()

    MiniServiceEditScreen(
        screenState = screenState,
        onNavigateBackClick = { navController.popBackStack() },
        onSubmitClick = viewModel::onSubmitClick,
    )
}

@Composable
private fun MiniServiceEditScreen(
    screenState: MiniServiceEditScreenState,
    onNavigateBackClick: () -> Unit,
    onSubmitClick: (MiniServiceRequest) -> Unit,
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
            MiniServiceAddFields(
                miniService = screenState.editedMiniService ?: MiniServiceRequest("", ""),
                onSubmitClick = onSubmitClick,
            )
        }
    }
}