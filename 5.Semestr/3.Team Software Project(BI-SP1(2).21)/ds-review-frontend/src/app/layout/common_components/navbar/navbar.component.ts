import { Component } from '@angular/core'
import { EventEmitter } from '@angular/core'
import { Output } from '@angular/core'
import {
  MatSlideToggleChange,
} from '@angular/material/slide-toggle'
import { Router } from '@angular/router'
@Component({
  selector: 'app-navbar',
  templateUrl: './navbar.component.html',
  styleUrls: ['./navbar.component.scss'],
})
export class NavbarComponent {
  @Output() darkModeSwitched = new EventEmitter<boolean>()

  constructor(private router: Router) {}

  // Call this function when the dark mode is toggled
  onDarkModeSwitched({ checked }: MatSlideToggleChange) {
    this.darkModeSwitched.emit(checked)
  }

  homeClicked() {
    this.router.navigate(['/me'])
  }
}
