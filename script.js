// ==== Общее ====
function goToMenu() {
    document.querySelectorAll(".game").forEach(el => el.classList.add("hidden"));
    document.getElementById("menu").classList.remove("hidden");
}

// ==== Игра "Угадай мем" ====

const allMemes = [
    { name: "Doge", file: "doge.jpg" },  // если есть
    { name: "Grumpy Cat", file: "grumpy-cat.jpg" },  // если есть
    { name: "Success Kid", file: "successkid.jpg" },  // если есть
    { name: "Distracted Boyfriend", file: "distracted-boyfriend.jpg" },
    { name: "Roll Safe", file: "Roll_Safe.jpg" },
    { name: "Philosoraptor", file: "Philosoraptor-meme.jpg" },
    { name: "Hide the Pain Harold", file: "hide-the-pain-harold.jpg" }
];


let memesDifficulty = "easy";
let currentMemeAnswer = "";

function shuffleArray(array) {
    const arr = array.slice();
    for (let i = arr.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [arr[i], arr[j]] = [arr[j], arr[i]];
    }
    return arr;
}

function loadMeme() {
    let optionsCount = 3;
    if (memesDifficulty === "medium") optionsCount = 5;
    else if (memesDifficulty === "hard") optionsCount = 7;

    const memeOptions = shuffleArray(allMemes).slice(0, optionsCount);
    const memeToGuess = memeOptions[Math.floor(Math.random() * memeOptions.length)];
    currentMemeAnswer = memeToGuess.name;

    const img = document.getElementById("meme-image");
    img.src = memeToGuess.file;
    img.alt = memeToGuess.name;

    const buttonsDiv = document.getElementById("meme-buttons");
    buttonsDiv.innerHTML = "";

    shuffleArray(memeOptions).forEach(meme => {
        const btn = document.createElement("button");
        btn.textContent = meme.name;
        btn.onclick = () => checkMemeAnswer(meme.name);
        buttonsDiv.appendChild(btn);
    });

    document.getElementById("meme-result").textContent = "";
}

function checkMemeAnswer(selected) {
    const result = document.getElementById("meme-result");
    if (selected === currentMemeAnswer) {
        result.textContent = "✅ Верно!";
    } else {
        result.textContent = `❌ Неверно! Это был ${currentMemeAnswer}.`;
    }
}

// ==== Игра "Угадай число" ====

let secretNumber = 0;
let numberDifficulty = "easy";

function startNumberGame() {
    const range = getNumberRange(numberDifficulty);
    secretNumber = Math.floor(Math.random() * (range.max - range.min + 1)) + range.min;

    const input = document.getElementById("guess-input");
    input.value = "";
    input.min = range.min;
    input.max = range.max;
    input.placeholder = `Введите число от ${range.min} до ${range.max}`;

    document.getElementById("guess-result").textContent = "";
    console.log("Загадано число:", secretNumber); // для отладки
}

function getNumberRange(level) {
    if (level === "easy") return { min: 1, max: 20 };
    if (level === "medium") return { min: 1, max: 50 };
    return { min: 1, max: 100 };
}

function checkGuess() {
    const input = document.getElementById("guess-input");
    const guess = parseInt(input.value);
    const result = document.getElementById("guess-result");

    if (isNaN(guess)) {
        result.textContent = "Введите число!";
        return;
    }
    if (guess < input.min || guess > input.max) {
        result.textContent = `Число должно быть от ${input.min} до ${input.max}`;
        return;
    }
    if (guess === secretNumber) {
        result.textContent = "🎉 Верно!";
    } else if (guess < secretNumber) {
        result.textContent = "🔼 Слишком мало!";
    } else {
        result.textContent = "🔽 Слишком много!";
    }
}

// ==== Игра "Лабиринт" ====

const canvas = document.getElementById("maze-canvas");
const ctx = canvas.getContext("2d");

let mazeSize = 4;
let mazeGrid = [];
let mazeVisited = [];
let mazeStack = [];

let playerPos = { x: 0, y: 0 };
let exitPos = { x: 0, y: 0 };

function initMaze(size) {
    mazeSize = size;
    mazeGrid = [];
    mazeVisited = [];
    mazeStack = [];

    // Создаем пустой лабиринт с 4 стенами вокруг каждой клетки
    for (let y = 0; y < mazeSize; y++) {
        mazeGrid[y] = [];
        mazeVisited[y] = [];
        for (let x = 0; x < mazeSize; x++) {
            mazeGrid[y][x] = { top: true, right: true, bottom: true, left: true };
            mazeVisited[y][x] = false;
        }
    }

    // Генерируем лабиринт (DFS)
    carveMaze(0, 0);

    playerPos = { x: 0, y: 0 };
    exitPos = { x: mazeSize - 1, y: mazeSize - 1 };

    drawMaze();
    document.getElementById("maze-status").textContent = "Используйте стрелки для перемещения. Дойдите до правого нижнего угла.";
}

function carveMaze(cx, cy) {
    mazeVisited[cy][cx] = true;
    const directions = shuffleArray(["top", "right", "bottom", "left"]);

    for (const dir of directions) {
        let nx = cx;
        let ny = cy;
        if (dir === "top") ny = cy - 1;
        else if (dir === "right") nx = cx + 1;
        else if (dir === "bottom") ny = cy + 1;
        else if (dir === "left") nx = cx - 1;

        if (nx >= 0 && nx < mazeSize && ny >= 0 && ny < mazeSize && !mazeVisited[ny][nx]) {
            // Убираем стену между текущей клеткой и соседней
            if (dir === "top") {
                mazeGrid[cy][cx].top = false;
                mazeGrid[ny][nx].bottom = false;
            } else if (dir === "right") {
                mazeGrid[cy][cx].right = false;
                mazeGrid[ny][nx].left = false;
            } else if (dir === "bottom") {
                mazeGrid[cy][cx].bottom = false;
                mazeGrid[ny][nx].top = false;
            } else if (dir === "left") {
                mazeGrid[cy][cx].left = false;
                mazeGrid[ny][nx].right = false;
            }
            carveMaze(nx, ny);
        }
    }
}

function drawMaze() {
    const cellSize = canvas.width / mazeSize;
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.strokeStyle = "#007acc";
    ctx.lineWidth = 2;

    for (let y = 0; y < mazeSize; y++) {
        for (let x = 0; x < mazeSize; x++) {
            const cell = mazeGrid[y][x];
            const px = x * cellSize;
            const py = y * cellSize;

            if (cell.top) {
                ctx.beginPath();
                ctx.moveTo(px, py);
                ctx.lineTo(px + cellSize, py);
                ctx.stroke();
            }
            if (cell.right) {
                ctx.beginPath();
                ctx.moveTo(px + cellSize, py);
                ctx.lineTo(px + cellSize, py + cellSize);
                ctx.stroke();
            }
            if (cell.bottom) {
                ctx.beginPath();
                ctx.moveTo(px, py + cellSize);
                ctx.lineTo(px + cellSize, py + cellSize);
                ctx.stroke();
            }
            if (cell.left) {
                ctx.beginPath();
                ctx.moveTo(px, py);
                ctx.lineTo(px, py + cellSize);
                ctx.stroke();
            }
        }
    }

    // Нарисовать игрока (красный квадрат)
    ctx.fillStyle = "red";
    ctx.fillRect(playerPos.x * cellSize + cellSize * 0.2, playerPos.y * cellSize + cellSize * 0.2, cellSize * 0.6, cellSize * 0.6);

    // Нарисовать выход (зелёный квадрат)
    ctx.fillStyle = "green";
    ctx.fillRect(exitPos.x * cellSize + cellSize * 0.25, exitPos.y * cellSize + cellSize * 0.25, cellSize * 0.5, cellSize * 0.5);
}

function movePlayer(dx, dy) {
    const x = playerPos.x;
    const y = playerPos.y;
    const cell = mazeGrid[y][x];

    if (dx === -1 && !cell.left) {
        playerPos.x--;
    } else if (dx === 1 && !cell.right) {
        playerPos.x++;
    } else if (dy === -1 && !cell.top) {
        playerPos.y--;
    } else if (dy === 1 && !cell.bottom) {
        playerPos.y++;
    } else {
        return; // нельзя ходить через стены
    }
    drawMaze();
    if (playerPos.x === exitPos.x && playerPos.y === exitPos.y) {
        document.getElementById("maze-status").textContent = "🎉 Вы прошли лабиринт!";
    }
}

document.addEventListener("keydown", e => {
    if (!document.getElementById("maze-game").classList.contains("hidden")) {
        if (["ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight"].includes(e.key)) {
            e.preventDefault();
            if (e.key === "ArrowUp") movePlayer(0, -1);
            if (e.key === "ArrowDown") movePlayer(0, 1);
            if (e.key === "ArrowLeft") movePlayer(-1, 0);
            if (e.key === "ArrowRight") movePlayer(1, 0);
        }
    }
});

// ==== Запуск игр ====

function startGame(game) {
    document.getElementById("menu").classList.add("hidden");
    document.querySelectorAll(".game").forEach(el => el.classList.add("hidden"));

    if (game === "memes") {
        memesDifficulty = document.getElementById("memes-difficulty").value;
        document.getElementById("memes-game").classList.remove("hidden");
        loadMeme();

    } else if (game === "number") {
        numberDifficulty = document.getElementById("number-difficulty").value;
        document.getElementById("number-game").classList.remove("hidden");
        startNumberGame();

    } else if (game === "maze") {
        const diff = document.getElementById("maze-difficulty").value;
        let size = 4;
        if (diff === "medium") size = 6;
        else if (diff === "hard") size = 8;
        document.getElementById("maze-game").classList.remove("hidden");
        initMaze(size);
    }
}
