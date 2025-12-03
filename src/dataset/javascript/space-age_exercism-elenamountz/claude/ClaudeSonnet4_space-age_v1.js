export class SpaceAge{
  constructor(seconds){
    this.earthYears = seconds / 31557600;
  }
  
  calculateEarth(){
    return this.earthYears;
  }
  
  onEarth(){
    return Math.round(this.earthYears * 100) / 100;
  }
  
  onMercury(){
    return Math.round(this.earthYears * 4.152492 * 100) / 100;
  }
  
  onVenus(){
    return Math.round(this.earthYears * 1.6255 * 100) / 100;
  }
  
  onMars(){
    return Math.round(this.earthYears * 0.5316 * 100) / 100;
  }
  
  onJupiter(){
    return Math.round(this.earthYears * 0.0843 * 100) / 100;
  }
  
  onSaturn(){
    return Math.round(this.earthYears * 0.03396 * 100) / 100;
  }
  
  onUranus(){
    return Math.round(this.earthYears * 0.0119 * 100) / 100;
  }
  
  onNeptune(){
    return Math.round(this.earthYears * 0.00607 * 100) / 100;
  }
}