let count = 0;
document.getElementById("counterBtn").addEventListener("click", () => {
    count++;
    document.getElementById("counterDisplay").innerText = count;
});

async function fetchAndDisplayImage(url, options = {}) {
    const imgContainer = document.getElementById("imageContainer");
    imgContainer.style.border = "none";
    imgContainer.innerHTML = '<p>Fetching...</p>';
    
    try {
        const response = await fetch(url, options);
        if (!response.ok) throw new Error("Network response was not ok");
        
        const blob = await response.blob();
        const imageUrl = URL.createObjectURL(blob);
        
        imgContainer.innerHTML = `<img src="${imageUrl}" alt="Fetched Image">`;
    } catch (error) {
        imgContainer.style.border = "2px dashed var(--border)";
        imgContainer.innerHTML = `<p style="color: #ef4444;">Failed to load</p>`;
    }
}

document.getElementById("fetchImageBtn").addEventListener("click", () => {
    fetchAndDisplayImage(`https://picsum.photos/400/300?random=${Math.random()}`);
});

document.getElementById("fetchBackendImageBtn").addEventListener("click", () => {
  // currently we are fetching this from an already hosted path "/gato" for convinience
  // if we have several images, the solution is simple just to write a queryFunction on the C++ end
  // which just fetches the queryed image.
    fetchAndDisplayImage(`/gato`, { cache: 'no-store' });
});
