//
//  ShowLocationOnMapView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 12.02.2023.
//

import SwiftUI
import MapKit

struct ShowLocationOnMapView: View {
    
    @Binding var mapAPI: MapAPI
    
    @Environment(\.dismiss) private var dismiss
    
    init(mapAPI: Binding<MapAPI>) {
        self._mapAPI = mapAPI
    }
    
    var body: some View {
        VStack {
            Button("Close map") {
                dismiss()
            }
            Map(coordinateRegion: $mapAPI.region, annotationItems: mapAPI.locations) { location in
                MapMarker(coordinate: location.coordinate, tint: .blue)
            }
            .ignoresSafeArea()
        }
        .toolbar(.hidden, for: .tabBar)
    }
}

struct ShowLocationOnMapView_Previews: PreviewProvider {
    
    @State static var mapAPI = MapAPI()
    
    static var previews: some View {
        ShowLocationOnMapView(mapAPI: $mapAPI)
    }
}
