package cz.cvut.kuznear1.activitiesfragments.ui

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material.Button
import androidx.compose.material.Scaffold
import androidx.compose.material.Text
import androidx.compose.material.TextField
import androidx.compose.material.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import cz.cvut.kuznear1.activitiesfragments.R

@Composable
fun MainActivityScreen(
    onAddActivityClick: () -> Unit,
) {
    Scaffold(
        topBar = {
            TopAppBar(title = { Text(text = stringResource(R.string.app_name)) })
        },
    ) { paddingValues ->
        Column(
            modifier = androidx.compose.ui.Modifier
                .padding(paddingValues)
                .fillMaxSize()
        ) {
            Column(
                modifier = Modifier
                    .padding(16.dp)
                    .fillMaxWidth()
            ) {
                Button(onClick = onAddActivityClick) {
                    Text("Add activity")
                }

                Spacer(Modifier.height(16.dp))

                var text by rememberSaveable { mutableStateOf("") }
                TextField(text, onValueChange = { text = it })
            }
        }
    }
}