package cz.cvut.fit.kuznear1.firebase.features.profile.presentation

import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.navigation.NavController
import com.firebase.ui.auth.AuthUI
import com.firebase.ui.auth.FirebaseAuthUIActivityResultContract
import cz.cvut.fit.kuznear1.firebase.R
import org.koin.androidx.compose.koinViewModel

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun ProfileScreen(
    navController: NavController,
    viewModel: ProfileViewModel = koinViewModel(),
) {
    val state by viewModel.screenStateStream.collectAsStateWithLifecycle()

    val launcher = rememberLauncherForActivityResult(
        contract = FirebaseAuthUIActivityResultContract(),
        onResult = {}
    )

    Scaffold(
        topBar = {
            TopAppBar(
                title = {
                    Text(stringResource(id = R.string.profile))
                },
                navigationIcon = {
                    IconButton(onClick = { navController.popBackStack() }) {
                        Icon(Icons.Default.ArrowBack, contentDescription = null)
                    }
                },
            )
        },
    ) { paddingValues ->
        Column(
            modifier = Modifier
                .padding(paddingValues)
                .padding(12.dp)
                .fillMaxSize(),
        ) {
            Text(stringResource(id = R.string.id), style = MaterialTheme.typography.titleMedium)

            Text(state.id ?: "-")

            Spacer(Modifier.height(12.dp))

            Text(stringResource(id = R.string.name), style = MaterialTheme.typography.titleMedium)

            Text(state.name ?: "-")

            Spacer(Modifier.height(12.dp))

            Spacer(Modifier.weight(1f))

            Button(
                onClick = {
                    val providers = arrayListOf(
                        AuthUI.IdpConfig.GoogleBuilder().build(),
                    )
                    val signInIntent = AuthUI.getInstance()
                        .createSignInIntentBuilder()
                        .setAvailableProviders(providers)
                        .build()
                    launcher.launch(signInIntent)
                },
                modifier = Modifier.fillMaxWidth(),
            ) {
                Text(stringResource(id = R.string.log_in))
            }

            Button(
                onClick = {
                    viewModel.logOut()
                },
                modifier = Modifier.fillMaxWidth(),
            ) {
                Text(stringResource(id = R.string.log_out))
            }
        }
    }
}
