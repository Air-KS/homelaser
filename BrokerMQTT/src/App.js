import React, { useState } from 'react';
import './App.css';

function App() {
  const [backgroundColor, setBackgroundColor] = useState('white');

  const changeColor = (color) => {
    setBackgroundColor(color);
  };

  document.body.style.backgroundColor = backgroundColor;

  return (
    <div className="container">
      <p><strong>Vous avez choisi la couleur {backgroundColor} pour votre page.</strong></p>
      <div className="buttonColor">
        <button className="colorButton" style={{ backgroundColor: 'red' }} onClick={() => changeColor('Red')}>Rouge</button>
        <button className="colorButton" style={{ backgroundColor: 'green' }} onClick={() => changeColor('Green')}>Vert</button>
        <button className="colorButton" style={{ backgroundColor: 'blue' }} onClick={() => changeColor('Blue')}>Bleu</button>
        <button className="colorButton" style={{ backgroundColor: 'yellow' }} onClick={() => changeColor('Yellow')}>Jaune</button>
        <button className="colorButton" style={{ backgroundColor: 'grey' }} onClick={() => changeColor('Grey')}>Gris</button>
      </div>
    </div>
  );
}

export default App;
