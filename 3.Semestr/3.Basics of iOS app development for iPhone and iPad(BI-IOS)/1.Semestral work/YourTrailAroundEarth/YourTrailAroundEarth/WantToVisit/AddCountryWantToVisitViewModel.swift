//
//  AddCountryWantToVisitViewModel.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 02.02.2023.
//

import MapKit

enum MapDetail {
    static let startingLocation = CLLocationCoordinate2D(latitude: 49.8175, longitude: 15.4730)
    static let defaultSpan = MKCoordinateSpan(latitudeDelta: 30, longitudeDelta: 30)
}

final class ContentViewModel: NSObject, ObservableObject, CLLocationManagerDelegate {
    var locationManager: CLLocationManager?
    
    @Published var region = MKCoordinateRegion(center: MapDetail.startingLocation, span: MapDetail.defaultSpan)
    
    func checkIfLocationServicesIsEnabled() {
        if CLLocationManager.locationServicesEnabled() {
            locationManager = CLLocationManager()
            locationManager!.delegate = self
        } else {
            print("Show alert!")
        }
    }
    
    private func checkLocationAuthorization() {
        guard let locationManager = locationManager else { return }
        
        switch locationManager.authorizationStatus {
            
        case .notDetermined:
            locationManager.requestWhenInUseAuthorization()
        case .restricted:
            print("Your location is restricted likely due to parental control.")
        case .denied:
            print("Your have denied this app location permission. Go into settings to change it .")
        case .authorizedAlways, .authorizedWhenInUse:
            region = MKCoordinateRegion(center: locationManager.location!.coordinate, span: MapDetail.defaultSpan)
        @unknown default:
            break
        }
    }
        
    func locationManagerDidChangeAuthorization(_ manager: CLLocationManager) {
        checkLocationAuthorization()
    }
}
