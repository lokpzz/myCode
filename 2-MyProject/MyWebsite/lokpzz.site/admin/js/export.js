// 数据导出工具 - 将后台数据同步到首页

function exportData() {
    const data = JSON.parse(localStorage.getItem('zyyoAdminData'));
    if (!data) {
        alert('没有可导出的数据');
        return;
    }

    // 这里应该调用后端 API 来更新实际的文件
    // 由于是纯静态网站，我们提供手动更新指南
    
    console.log('导出数据:', data);
    
    // 生成配置文件的建议
    const configContent = `
// 这是根据后台数据生成的配置文件
// 您可以将此内容手动更新到 index.html 或 script.js 中

const siteConfig = ${JSON.stringify(data, null, 2)};
`;
    
    // 下载配置文件
    downloadFile(configContent, 'site-config.js', 'text/javascript');
    
    alert('配置文件已下载！\n\n由于这是纯静态网站，您需要手动将数据更新到 index.html 文件中。\n\n未来版本将支持自动更新。');
}

function downloadFile(content, filename, type) {
    const blob = new Blob([content], { type: type });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = filename;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
}

// 在页面加载时检查更新
document.addEventListener('DOMContentLoaded', function() {
    // 可以在这里添加自动同步逻辑
});
