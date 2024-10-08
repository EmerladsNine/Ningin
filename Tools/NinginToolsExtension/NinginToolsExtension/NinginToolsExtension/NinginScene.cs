using Microsoft.VisualStudio.Text;
using Microsoft.VisualStudio.Text.Classification;
using Microsoft.VisualStudio.Text.Tagging;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace NinginToolsExtension
{
    /// <summary>
    /// Classifier that classifies all text as an instance of the "NinginScene" classification type.
    /// </summary>
    internal class NinginScene : IClassifier
    {
        /// <summary>
        /// Classification type.
        /// </summary>
        private readonly IClassificationType classificationType;
        private readonly IClassificationType _keywordType;
        private readonly IClassificationType _commentType;


        /// <summary>
        /// Initializes a new instance of the <see cref="NinginScene"/> class.
        /// </summary>
        /// <param name="registry">Classification registry.</param>
        internal NinginScene(ITextBuffer buffer, IClassificationTypeRegistryService registry)
        {
            Debug.WriteLine("GetClassifier called for buffer: " + buffer);
            this.classificationType = registry.GetClassificationType("NinginScene");
            _keywordType = registry.GetClassificationType("NinginSceneKeyword");
            _commentType = registry.GetClassificationType("NinginSceneComment");
        }

        #region IClassifier

#pragma warning disable 67

        /// <summary>
        /// An event that occurs when the classification of a span of text has changed.
        /// </summary>
        /// <remarks>
        /// This event gets raised if a non-text change would affect the classification in some way,
        /// for example typing /* would cause the classification to change in C# without directly
        /// affecting the span.
        /// </remarks>
        public event EventHandler<ClassificationChangedEventArgs> ClassificationChanged;

#pragma warning restore 67

        /// <summary>
        /// Gets all the <see cref="ClassificationSpan"/> objects that intersect with the given range of text.
        /// </summary>
        /// <remarks>
        /// This method scans the given SnapshotSpan for potential matches for this classification.
        /// In this instance, it classifies everything and returns each span as a new ClassificationSpan.
        /// </remarks>
        /// <param name="span">The span currently being classified.</param>
        /// <returns>A list of ClassificationSpans that represent spans identified to be of this classification.</returns>
        public IList<ClassificationSpan> GetClassificationSpans(SnapshotSpan span)
        {

            string text = span.GetText();

            // Example: Check for keywords in the text
            if (IsKeyword(text))
            {
                var result2 = new List<ClassificationSpan>()
                {
                    new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(span.Start, span.Length)), this._keywordType)
                };

                return result2;
            }

            // Example: Check for comments in the text
            if (IsComment(text))
            {
                var result2 = new List<ClassificationSpan>()
                {
                    new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(span.Start, span.Length)), this._commentType)
                };

                return result2;
            }

            var result = new List<ClassificationSpan>()
                {
                    new ClassificationSpan(new SnapshotSpan(span.Snapshot, new Span(span.Start, span.Length)), this.classificationType)
                };

            return result;
        }

        private bool IsKeyword(string text)
        {
            // List of keywords for the custom language
            var keywords = new[] { "if", "else", "while", "return" };
            return keywords.Contains(text);
        }

        // Dummy method to check if text is a comment
        private bool IsComment(string text)
        {
            return text.StartsWith("//");
        }

        #endregion
    }
}
