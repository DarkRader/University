//
//  AddCountryWantToVisitView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 02.02.2023.
//

import MapKit
import SwiftUI

struct AddCountryWantToVisitView: View {
    @StateObject private var viewModel = ContentViewModel()
    
    var body: some View {
        Map(coordinateRegion: $viewModel.region, showsUserLocation: true)
            .ignoresSafeArea()
            .accentColor(Color(.systemPink))
            .onAppear {
                viewModel.checkIfLocationServicesIsEnabled()
            }
    }
}

struct AddCountryWantToVisitView_Previews: PreviewProvider {
    static var previews: some View {
        AddCountryWantToVisitView()
            .preferredColorScheme(.light)
        AddCountryWantToVisitView()
            .preferredColorScheme(.dark)
    }
}
