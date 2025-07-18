//
//  LandmarkAnnotation.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 03.02.2023.
//

import MapKit
import UIKit


final class LandmarkAnnotation: NSObject, MKAnnotation {
    let title: String?
    let coordinate: CLLocationCoordinate2D

    init(landmark: Landmark) {
        self.title = landmark.name
        self.coordinate = landmark.coordinate
    }
}
